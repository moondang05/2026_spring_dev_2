#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
private:
    // TODO: 실수부 real, 허수부 imag (double) 선언
    double real;
    double imag;

public:
    // TODO: 생성자 선언 — 기본 매개변수 0.0, 0.0 사용
    Complex(double real = 0.0, double imag = 0.0);

    // TODO: 산술 연산자 선언 (멤버 함수, const, const&)
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;

    // TODO: 비교 연산자 선언 (멤버 함수)
    bool operator<(const Complex& other) const;

    // TODO: 출력 연산자 선언 (friend, 비멤버)
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endif // COMPLEX_H
