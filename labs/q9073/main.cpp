#include <iostream>
#include "Matrix.hpp"

static void print_matrix(const char* label, const Matrix& m) {
    std::cout << label << "\n" << m;
}

static int read_const_entry(const Matrix& m) { return m[1, 1]; }

int main() {
    // ======= 2x2 Matrix Tests =======
    std::cout << "===== 2x2 Matrix Tests =====\n";
    Matrix m2a = {{ 4,  1}, {-7, -3}};
    Matrix m2b = {{ 1,  1}, { 0,  0}};

    Matrix m2c = m2a + m2b;
    m2c[0, 1] = m2c[0, 1] + 10;
    print_matrix("m2a", m2a);
    print_matrix("m2b", m2b);
    print_matrix("m2c = m2a + m2b; m2c[0, 1] += 10", m2c);
    std::cout << "const read m2c[1, 1]: " << read_const_entry(m2c) << "\n";

    // ======= 3x3 Matrix Tests =======
    std::cout << "\n===== 3x3 Matrix Tests =====\n";
    Matrix m3a = {{2,  3,  0}, {1, -2, -1}, {2,  0, -1}};
    Matrix m3b = {{-1, -1, 3}, {-1,  2,  1}, {3,  6,  1}};

    Matrix m3c = m3a + m3b;
    m3c[1, 1] = 1; m3c[1, 2] = 4;
    print_matrix("m3a", m3a);
    print_matrix("m3b", m3b);
    print_matrix("m3c = m3a + m3b; m3c[1, 1] = 1; m3c[1, 2] = 4", m3c);

    // ======= Additional Operator Tests =======
    std::cout << "\n===== Additional Operator Tests =====\n";
    Matrix a = {{1, 2}, {3, 4}};
    Matrix b = {{5, 6}, {7, 8}};
    Matrix c = a * b;
    Matrix d = a - Matrix({{1, 1}, {1, 1}});
    d[1, 0] = d[1, 0] + 5;

    print_matrix("a", a);
    print_matrix("b", b);
    print_matrix("a * b", c);
    print_matrix("a - {{1,1},{1,1}}; d[1, 0] += 5", d);
    std::cout << "a == a: " << std::boolalpha << (a == a) << "\n";
    std::cout << "a != d: " << (a != d) << "\n";

    return 0;
}
