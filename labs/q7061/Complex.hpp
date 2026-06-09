#ifndef COMPLEX_H
#define COMPLEX_H

#include <string>

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0);
    Complex add(const Complex& other) const;
    std::string print() const;

private:
    double real;
    double imag;
};

#endif // COMPLEX_H
