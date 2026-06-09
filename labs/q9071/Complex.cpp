#include "Complex.h"
#include <cmath>

// TODO: Complex.h 에 선언된 함수/연산자를 모두 구현하세요.
// - 생성자 (멤버 초기화 리스트)
// - operator+ , operator-  (새 Complex 반환, const)
// - operator<              (magnitude → real → imag 순으로 tie-break)
// - operator<<             (friend, 비멤버)
//
// 모든 산술·비교 연산자는 *this 와 other 를 수정하지 않습니다 (const).

Complex::Complex(double real, double imag) : real(real), imag(imag)
{
}

// TODO: operator+ 구현 — 두 복소수의 실수부·허수부를 각각 더한 새 객체 반환
Complex Complex::operator+(const Complex &other) const
{
    double r = real + other.real;
    double i = imag + other.imag;
    return Complex(r, i);
}

// TODO: operator- 구현 — 두 복소수의 실수부·허수부를 각각 뺀 새 객체 반환
Complex Complex::operator-(const Complex &other) const
{
    double r = real - other.real;
    double i = imag - other.imag;
    return Complex(r, i);
}

// TODO: operator< 구현
//   1) 크기(magnitude = sqrt(real^2 + imag^2)) 로 먼저 비교
//   2) 크기가 같으면 real 값으로 비교
//   3) real 도 같으면 imag 값으로 비교
//   → 이 3단계 tie-break 이 있어야 std::map 이 서로 다른 복소수를 구분합니다.
bool Complex::operator<(const Complex &other) const
{
    auto m1 = std::sqrt(real * real + imag * imag);
    auto m2 = std::sqrt((other.real) * (other.real) + (other.imag) * (other.imag));
    if (m1 != m2)
        return m1 < m2;
    if (real != other.real)
        return real < other.real;
    return imag < other.imag;
}

// TODO: operator<< 구현 (friend, 비멤버)
//   - real==0 && imag==0  →  "0"
//   - imag==0             →  "<real>"
//   - real==0             →  "<imag>i"
//   - else, imag>0        →  "<real>+<imag>i"
//   - else                →  "<real><imag>i"    // imag 자체에 '-' 가 붙어 있음
std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    // if (c.real == 0 && c.imag == 0)
    //     os << "0";
    // else if (c.imag == 0 && c.real != 0)
    //     os << c.real;
    // else if (c.real == 0 && c.imag != 0)
    //     os << c.imag << "i";
    // else if (c.imag > 0)
    //     os << c.real << "+" << c.imag << "i";
    // else
    //     os << c.real << c.imag << "i";

    if (c.real ==0 && c.imag) os << "0";
    else if ( c.imag ==0) os<<c.real;
    else if ( c.real ==0) os<<c.imag<<"i";
    else os << c.real << ((c.imag>0)?"+":"")<<c.imag<<"i";

    return os;
}