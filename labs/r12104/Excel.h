#pragma once

#include "Cell.h"

#include <cstddef>
#include <initializer_list>
#include <mdspan>
#include <ranges>
#include <string>
#include <vector>

// TODO: Excel 클래스를 완성하세요.
//
// 핵심 요구 사항 (배경지식·문제 설명 참조)
//   1) 데이터는 std::vector<Cell> 한 줄에 평탄(flat)하게 보관한다.
//   2) operator[] 는 C++23 deducing this + 다차원 첨자 연산자로 작성한다.
//      본체에서는 std::mdspan(data, rows, cols)[r, c] 를 호출한다.
//   3) cells() 는 std::views::cartesian_product / iota / transform 으로
//      직사각 영역 view 를 돌려준다. 호출 측에서 알고리즘으로 소비한다.
//   4) ① 생성자는 직사각형이 아닌 입력에 std::invalid_argument 를 던진다.
//   5) check_index / check_range 는 잘못된 좌표에 std::out_of_range 를 던진다.
//   6) 좌표는 STL 의 [first, last) half-open 으로 통일한다.
class Excel
{
public:
    Excel(std::initializer_list<std::initializer_list<Cell>> init);
    Excel(std::size_t rows, std::size_t cols);

    [[nodiscard]] std::size_t rows() const noexcept { return rows_; }
    [[nodiscard]] std::size_t cols() const noexcept { return cols_; }

    // TODO: deducing this(this auto&& self) + std::mdspan 다차원 첨자로
    // 한 함수에서 const/non-const 양쪽을 모두 처리하도록 본문을 교체하세요.
    //   힌트:  self.check_index(r, c);
    //          std::mdspan(self.data_.data(), self.rows_, self.cols_)[r, c];
    // 아래 placeholder 는 컴파일만 가능하도록 둔 더미 — 항상 (0, 0) 셀을
    // 돌려주므로 채점은 실패합니다.
    decltype(auto) operator[](this auto &&self, std::size_t r, std::size_t c)
    {
        self.check_index(r, c);
        return std::mdspan(self.data_.data(), self.rows_, self.cols_)[r, c];
    }

    // TODO: std::views::cartesian_product + std::views::iota + std::views::transform
    // 으로 직사각 영역 [r1, r2) × [c1, c2) 를 가리키는 view 를 돌려주세요.
    // 아래는 항상 빈 view 를 돌려주는 placeholder 입니다 — 평균이 0.0 으로
    // 떨어집니다.
    [[nodiscard]] auto cells(std::size_t r1, std::size_t c1,
                             std::size_t r2, std::size_t c2) const
    {
        check_range(r1, c1, r2, c2);
        namespace v = std::views;
        return v::cartesian_product(v::iota(r1, r2), v::iota(c1, c2)) | v::transform([this](auto rc)
                                                                                     {auto [r, c] = rc;
         return std::mdspan(data_.data(), rows_, cols_)[r, c]; });
    }

    [[nodiscard]] double average(std::size_t r1, std::size_t c1,
                                 std::size_t r2, std::size_t c2) const;
    [[nodiscard]] std::string display() const;

private:
    std::vector<Cell> data_;
    std::size_t rows_{};
    std::size_t cols_{};

    void check_index(std::size_t r, std::size_t c) const;
    void check_range(std::size_t r1, std::size_t c1,
                     std::size_t r2, std::size_t c2) const;
};
