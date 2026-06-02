#include <iostream>
#include "Complex.hpp"

int main() {
    // [Most Vexing Parse 주의]
    // Complex c11();  ← 객체가 아닌 함수 선언!
    //                   Complex를 반환하는 함수로 해석됩니다.
    // 기본 생성자를 호출하려면 Complex c11; 또는 Complex c11{}; 를 사용하세요.

    Complex c0;                               // 기본 생성자 (real=0.0, imag=0.0)
    std::cout << c0.print();                  // 0.0+0.0i

    Complex c1(3.0, 4.0);                     // 일반 생성자
    std::cout << c1.print();                  // 3.0+4.0i

    Complex c2(5.0);                          // 단일 인수 (imag 기본값 0.0)
    std::cout << c2.print();                  // 5.0+0.0i

    Complex c3{1.0, 2.0};                     // uniform initialization
    std::cout << c3.print();                  // 1.0+2.0i

    Complex c4 = c1.add(c3);                  // (3+4i) + (1+2i)
    std::cout << c4.print();                  // 4.0+6.0i

    Complex c5 = c1.add(3.0);                 // double → Complex 암묵 변환: (3+4i) + (3+0i)
    std::cout << c5.print();                  // 6.0+4.0i

    Complex c6(2.0, -3.0);                    // 허수부가 음수
    std::cout << c6.print();                  // 2.0-3.0i

    Complex c7 = c6.add(Complex(0.0, 3.0));   // 임시 객체를 인수로
    std::cout << c7.print();                  // 2.0+0.0i

    return 0;
}
