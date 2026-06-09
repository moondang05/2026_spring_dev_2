#include "Vehicle.hpp"

// TODO: make_vehicle() 함수를 구현하세요.
// 매개변수 choice("gv70", "grandeur", "carnival") 값에 따라
// 해당 Vehicle 파생 클래스의 unique_ptr을 반환합니다.
std::unique_ptr<Vehicle> make_vehicle(const std::string& choice) {
    // TODO: 분기 처리
    if (choice == "gv70") {
        return std::make_unique<GV70>();
    }
    else if(choice=="grandeur") {
        return std::make_unique<Grandeur>();
    }
    else if (choice=="carnival")
    {
        return std::make_unique<Carnival>();
    }
    else if(choice=="ev6") {
        return std::make_unique<Ev6>();
    }
    
    return nullptr;
}
