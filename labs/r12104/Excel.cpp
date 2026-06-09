#include "Excel.h"

#include <algorithm>
#include <concepts>
#include <format>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

namespace
{

    // TODO: 평균에서 받아들일 "숫자" 타입을 정의하세요.
    //   * std::integral 또는 std::floating_point 면서
    //   * bool 은 제외 (진리값은 숫자가 아닙니다).
    template <class T>
    concept Number = (std::integral<std::remove_cvref_t<T>> || std::floating_point<std::remove_cvref_t<T>>) && !std::same_as<std::remove_cvref_t<T>, bool>;

    // 한 셀을 사람이 읽는 문자열로. double 은 소수점 1자리로 고정합니다.
    //   std::visit + generic lambda + if constexpr 의 조합을 익히는 자리.
    std::string format_cell(const Cell &cell)
    {
        return std::visit([]<class T>(const T &v) -> std::string
                          {
        using U = std::remove_cvref_t<T>;
        if constexpr (std::same_as<U, std::string>) {
            return v;
        } else if constexpr (std::floating_point<U>) {
            return std::format("{:.1f}", v);
        } else {
            return std::format("{}", v);
        } }, cell.value());
    }

} // namespace

// TODO: ① initializer_list 생성자.
//   * rows_ 는 행 수, cols_ 는 첫 행의 길이.
//   * 짧거나 긴 행을 만나면 std::invalid_argument 를 던지세요.
//     (조용히 빈 셀로 채우면 안 됩니다 — 직사각형 불변식이 무너지면 mdspan
//      이 잘못된 좌표를 만들기 시작합니다.)
Excel::Excel(std::initializer_list<std::initializer_list<Cell>> init)
    : rows_(init.size()),
      cols_(rows_ == 0 ? 0 : init.begin()->size())
{
    data_.reserve(rows_ * cols_);
    for (const auto &row : init)
    {
        if (row.size() != cols_)
        {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
        data_.insert(data_.end(), row);
    }
    // TODO: data_ 에 모든 셀을 평탄하게 담으세요.
    //       각 행의 길이가 cols_ 와 다르면 std::invalid_argument 를 던지세요.
}

// TODO: ② (rows, cols) 생성자.
//   기본값 Cell{} 로 채워진 빈 시트를 만드세요. data_(rows * cols) 한 줄.
Excel::Excel(std::size_t rows, std::size_t cols)
    : data_(rows * cols), rows_(rows), cols_(cols) {}

void Excel::check_index(std::size_t r, std::size_t c) const
{
    // TODO: r 이 rows_ 이상이거나 c 가 cols_ 이상이면 std::out_of_range 를 던지세요.
    if (r >= rows_ || c >= cols_)
    {
        throw std::out_of_range("Index out of range");
    }
}

void Excel::check_range(std::size_t r1, std::size_t c1,
                        std::size_t r2, std::size_t c2) const
{
    // TODO: r1 > r2 또는 c1 > c2 또는 r2 > rows_ 또는 c2 > cols_ 면 던지세요.
    // size_t 언더플로우와 시트 밖 좌표를 한꺼번에 차단합니다.
    if (r1 > r2 || c1 > c2 || r2 > rows_ || c2 > cols_)
    {
        throw std::out_of_range("Invalid range");
    }
}

// TODO: ranges::fold_left 로 (합, 개수) 를 누적하세요.
//   문자열 셀은 자동으로 무시 — std::visit 안의 if constexpr 가 분기합니다.
//   숫자가 한 개도 없으면 0.0 을 반환합니다 (0 으로 나누기 회피).
double Excel::average(std::size_t r1, std::size_t c1,
                      std::size_t r2, std::size_t c2) const
{
    auto [sum, count] = std::ranges::fold_left(
        cells(r1, c1, r2, c2), std::pair<double, int>{0.0, 0},
        [](auto acc, const Cell &cell) {
            auto [s, c] = acc;
            return std::visit([s, c](const auto &v) -> std::pair<double, int> {
                if constexpr (Number<decltype(v)>) {
                    return {s + static_cast<double>(v), c + 1};
                }
                return {s, c};
            }, cell.value());
        });

    return count == 0 ? 0.0 : sum / count;
}

// TODO: r=0..rows_, c=0..cols_ 의 모든 셀을 탭으로 구분해 한 줄에 한 행씩 출력.
//   * 각 행 끝에는 '\n' 한 번.
//   * c == 0 일 때는 앞에 탭을 붙이지 않습니다.
//   * 각 셀의 문자열화는 위쪽 namespace 의 format_cell 을 사용하세요.
std::string Excel::display() const
{
    std::ostringstream oss;
    for (std::size_t r = 0; r < rows_; r++)
    {
        for (std::size_t c = 0; c < cols_; c++)
        {
            if (c > 0)
                oss << '\t';
            oss << format_cell(std::mdspan(data_.data(), rows_, cols_)[r, c]);
        }
        oss << '\n';
    }
    return oss.str();
}
