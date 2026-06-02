#include "Vehicle.hpp"
#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<Vehicle>> test_vehicles;
    // 벡터에다가 이 클래스의 자식들을 담는 것이기 때문에 담을 수 있다~!

    test_vehicles.push_back(make_vehicle("gv70"));      // gv70
    test_vehicles.push_back(make_vehicle("grandeur"));  // grandeur
    test_vehicles.push_back(make_vehicle("carnival"));  // carnival
    test_vehicles.push_back(make_vehicle("ev6"));       // ev6

    for (auto& v : test_vehicles)
        v->accelerate();

    return 0;
}




// class OutputDevice {
//     public:
//         OutputDevice() {};
//         virtual void out() = 0;
// };

// class Moniter : public OutputDevice {
//     public:
//         void out() override {
//             std::cout<<"out!\n";
//         };
// };
