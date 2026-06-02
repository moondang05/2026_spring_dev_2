#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <span>

class Matrix {
private:
    int*        data;
    std::size_t rows;  // M
    std::size_t cols;  // N

    // 제공된 Helper — data 를 Range View 로 보는 창구입니다.
    // get_row(r), get_col(c) 를 활용하면 루프 없이 연산을 표현할 수 있습니다.
    std::span<int> as_span() const;
    auto get_row(std::size_t r) const;
    auto get_col(std::size_t c) const;

public:
    // TODO: 생성자 3 종
    Matrix() noexcept;
    // M x N                                                         // 0×0
    Matrix(std::size_t r, std::size_t c);                             // r×c, 0 초기화
    Matrix(std::initializer_list<std::initializer_list<int>> init);   // {{1,2},{3,4}}

    // TODO: Rule of Three — data 를 직접 관리하므로 3 개 모두 구현해야 합니다.
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();

    // C++23 다차원 첨자 — matrix[r, c] 사용 가능 (제공됨)
    int& operator[](std::size_t r, std::size_t c);
    const int& operator[](std::size_t r, std::size_t c) const;

    // TODO: 산술 연산자
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;

    // TODO: 비교 연산자
    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    // TODO: 스트림 출력 — 각 행을 "v1 v2 v3\n" 형태로 출력합니다.
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif
