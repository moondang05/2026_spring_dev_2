#include "Excel.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>

// TODO: 아래 함수들을 구현하세요.
// std::any_of 와 std::accumulate 를 반드시 사용해야 합니다.
// for_each 는 사용 금지입니다.

Excel::Excel(const Table &data) : data_{data}
{
    // 테이블 데이터를 멤버에 저장합니다.
}

std::vector<Cell> Excel::getCellsInRange(int fromRow, int fromCol,
                                         int toRow, int toCol) const
{
    // (fromRow, fromCol) ~ (toRow, toCol) 범위의 셀을 1차원 벡터로 반환합니다.
    // 인덱스는 1-based 입니다 (1행 1열이 첫 번째 셀).
    std::vector<Cell> base;
    for (int i = fromRow - 1; i < toRow; i++)
    {
        auto start = data_[i].begin() + (fromCol - 1);
        auto last = data_[i].begin() + (toCol);
        // 칸 속 내용이 아니라 그 칸 자체를 지칭하는 것

        base.insert(base.end(), start, last);
    }

    return base;
}

bool Excel::hasStringInRange(int fromRow, int fromCol,
                             int toRow, int toCol) const
{
    // 범위 안에 문자열 셀이 하나라도 있으면 true 를 반환합니다.
    // 힌트: std::any_of + 람다로 구현하세요.
    std::vector<Cell> scan = getCellsInRange(fromRow, fromCol, toRow, toCol);
    return std::any_of(scan.begin(), scan.end(), [](const Cell &c)
                       { return c.isString(); });
}

bool Excel::isValidRange(int fromRow, int fromCol,
                         int toRow, int toCol) const
{
    // 범위가 테이블 크기 안에 있는지 검증합니다.
    // 힌트: fromRow, fromCol, toRow, toCol 이 모두 양수이고
    //       fromRow <= toRow, fromCol <= toCol 인지 확인하세요.

    if (fromRow <= 0 || fromCol <= 0 || toRow <= 0 || toCol <= 0) return false;
    if (fromRow > toRow || fromCol > toCol) return false;
    if (data_.empty()) return false;
    if (toRow > static_cast<int>(data_.size()) || toCol > static_cast<int>(data_[0].size())) return false;
    return true;
}

double Excel::average(int fromRow, int fromCol,
                      int toRow, int toCol) const
{
    // 범위 내 숫자 셀의 평균을 반환합니다.
    // 1) getCellsInRange 로 셀 목록을 가져옵니다.
    // 2) std::accumulate + 람다로 숫자 값의 합을 구합니다.
    // 3) 숫자 셀 개수로 나눕니다.
    std::vector<Cell> list = getCellsInRange(fromRow, fromCol, toRow, toCol);

    if (list.empty())
        return 0.0;

    double sum = std::accumulate(list.begin(), list.end(), 0.0, [](double d, const Cell &c)
                                 { return d + c.getNumericValue(); });

    return sum / list.size();
}

std::string Excel::display() const
{
    // 테이블을 탭(\t) 구분 문자열로 반환합니다.
    // 각 행 끝에 줄바꿈(\n), 첫 줄 앞에도 줄바꿈을 넣습니다.
    // 힌트: std::ostringstream 을 사용하세요.

    std::ostringstream oss;
    oss << '\n';
    for (const auto &row : data_)
    {
        for (const auto &cell : row)
        {
            oss << cell.toString() << '\t';
        }
        oss << '\n';
    }
    return oss.str();
}
