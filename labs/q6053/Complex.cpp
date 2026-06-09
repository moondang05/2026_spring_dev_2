#include "Complex.hpp"
#include <sstream>
#include <iomanip>

// TODO: 아래 세 함수를 구현하세요.
// Complex 객체는 생성 후 상태가 변하지 않습니다 (불변 객체).
// add 함수는 새 Complex 객체를 반환해야 합니다.

// [Most Vexing Parse 주의]
// Complex c11();  ← 이것은 객체 선언이 아닙니다!
//                   Complex를 반환하는 함수 선언으로 해석됩니다.
// 올바른 기본 생성자 호출: Complex c11;  또는  Complex c11{};

Complex::Complex(double real, double imag) : real{real}, imag{imag}
// 힌트: 멤버 초기화 리스트를 사용하세요.
//       : real(real), imag(imag)
// 두 매개변수 모두 기본값(0.0)을 가지므로 Complex c; 도 동작합니다.
{
}

Complex Complex::add(const Complex &other) const
{
    // 두 복소수의 실수부와 허수부를 각각 더하여 새 Complex 객체를 반환합니다.
    // 주의: *this와 other를 수정하면 안 됩니다 (const).
    // 힌트: double 인수 1개로도 Complex가 암묵 생성됩니다 (변환 생성자).
    //       c1.add(3.0) → Complex(3.0, 0.0)이 자동 생성되어 더해집니다.
    auto real = Complex::real + other.real;
    auto imag = Complex::imag + other.imag;

    return Complex(real, imag);
}

std::string Complex::print() const
{
    // "3.0+4.0i\n" 또는 "3.0-4.0i\n" 형식으로 반환합니다.
    // 힌트: std::ostringstream + std::fixed + std::setprecision(1)
    // 힌트: imag >= 0이면 "+"를 명시적으로 추가하고, imag < 0이면 부호가 자동으로 붙습니다.
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << '\n';
    
    if (imag < 0)
    {
        oss << real << "-" << imag << 'i\n';
    }
    else
    {
        oss << real << "+" << imag << 'i\n';
    }

    return oss.str();
}
