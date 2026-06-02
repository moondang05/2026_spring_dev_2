#include "Temperature.h"
#include <sstream>
#include <iomanip>
#include <format>

// TODO: 아래 다섯 함수를 구현하세요.
// Temperature 객체는 생성 후 상태가 변하지 않습니다 (불변 객체).
// add 함수는 새 Temperature 객체를 반환해야 합니다.

Temperature::Temperature(double temp, Scale scale)
    // 힌트: 멤버 초기화 리스트를 사용하세요.
    : temperature(temp), scale(scale)   // 생성자 정리 (const인 것과 무관하게 사용 가능)
{
    // temperature = temp;
    // this->scale = scale;

    // // this는 자기 지시 포인터 
    // // 이름이 같을 때 받는 대상과 보내는 대상의 차이를 인식할 수 있음
    // // (만약 const로 선언되어 있으면? 에러가 발생)
}

double Temperature::toCelsius() const {
    // 이미 Celsius이면 그대로 반환합니다.
    // Fahrenheit이면 (temperature - 32) * 5.0 / 9.0 으로 변환합니다.


    // if (scale == Scale::Celsius) return temperature;
    // else if (scale == Scale::Fahrenheit) return (temperature - 32) * 5.0 / 9.0; 

    return (scale == Scale::Celsius) ? temperature 
                                    : (temperature - 32) * 5.0 / 9.0;
}

double Temperature::toFahrenheit() const {
    // 이미 Fahrenheit이면 그대로 반환합니다.
    // Celsius이면 temperature * 9.0 / 5.0 + 32 로 변환합니다.

    // if (scale == Scale::Fahrenheit) return temperature;
    // else if (scale == Scale::Celsius) return temperature * 9.0 / 5.0 + 32; 

    return (scale == Scale::Fahrenheit) ? temperature 
                                        : temperature * 9.0 / 5.0 + 32;

}

Temperature Temperature::add(const Temperature& other) const {
    // 호출자의 scale에 맞춰 결과를 반환합니다.
    // 예: this가 Celsius이면 other를 Celsius로 변환 후 더합니다.
    // 힌트: toCelsius() / toFahrenheit() 를 활용하세요.
    // 주의: *this 와 other 를 수정하면 안 됩니다 (const).


    // auto mid = other;
    // if (this->scale == Scale::Celsius)
    // {
    //     mid.toCelsius();
    // } else if (this->scale == Scale::Fahrenheit) {
    //     mid.toFahrenheit();
    // }
    
    // return Temperature(0.0);



    return (scale == Scale::Celsius) ? Temperature(temperature + other.toCelsius(), scale)
                                     : Temperature(temperature + other.toFahrenheit(), scale);
}

std::string Temperature::print() const {
    // "25.0 C\n" 또는 "77.0 F\n" 형식으로 반환합니다.
    // 힌트: std::ostringstream + std::fixed + std::setprecision(1)

    
    // std::ostringstream oss;
    // oss << std::fixed << std::setprecision(1) << temperature;
    // if (scale == Scale::Celsius) oss << " C\n";
    // else if (scale == Scale::Fahrenheit) oss << " F\n";
    // return oss.str();




    return (scale == Scale::Celsius) ? std::format("{:.1f} {}\n", temperature, "C") 
                                      :std::format("{:.1f} {}\n", temperature, "F");
}
