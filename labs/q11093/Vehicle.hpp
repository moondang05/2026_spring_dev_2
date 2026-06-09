#pragma once
#include <iostream>
#include <memory>
#include <string>

// TODO: Vehicle 추상 기반 클래스를 정의하세요.
// - accelerate()를 순수 가상 함수로 선언
// - 가상 소멸자 추가
class Vehicle {
public:
    virtual void accelerate() = 0;
    virtual ~Vehicle() = default;
};

// TODO: GV70, Grandeur, Carnival 클래스를 정의하세요 (Vehicle 상속).
// - accelerate() override: 각각의 속도 증가 메시지를 출력
//   GV70:     "The speed of the gv70 has increased by 30 km/h."
//   Grandeur: "The speed of the grandeur has increased by 20 km/h."
//   Carnival: "The speed of the carnival has increased by 10 km/h."

class GV70 : public Vehicle {
public:
    void accelerate() override {
        std::cout<<"The speed of the gv70 has increased by 30 km/h."<<std::endl;
    };
};

class Grandeur : public Vehicle {
public:
    void accelerate() override {
        std::cout<<"The speed of the grandeur has increased by 20 km/h."<<std::endl;
    };
};

class Carnival : public Vehicle {
public:
    void accelerate() override {
        std::cout<<"The speed of the carnival has increased by 10 km/h."<<std::endl;
    };
};

class Ev6 : public Vehicle {
public:
    void accelerate() override {
        std::cout<<"The speed of the ev6 has increased by 10 km/h."<<std::endl;
    };
};

// make_vehicle() 함수 선언 (Vehicle.cpp에서 구현)
// 전달받은 차종 이름에 맞는 파생 클래스 객체를 생성합니다.
std::unique_ptr<Vehicle> make_vehicle(const std::string& choice);
