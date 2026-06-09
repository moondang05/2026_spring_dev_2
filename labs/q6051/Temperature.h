#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <string>

enum class Scale {
    Celsius,
    Fahrenheit
};

class Temperature {
public:
    Temperature(double temp, Scale scale = Scale::Celsius /*디폴트 밸류 지정 가능함(선언하는 부분에서만(=정리할 때 지정하면 에러 남))*/);
    Temperature add(const Temperature& other) const;
    std::string print() const;

private:
    double temperature;
    Scale scale;

    double toCelsius() const;
    double toFahrenheit() const;
};      //클래스는 끝에 ;로 끝내야 함

#endif // TEMPERATURE_H
