#pragma once
#include "OutputDevice.h"

// TODO: Printer 클래스를 구현하세요 (OutputDevice를 public 상속).
// 생성자: "Printer constructor" 출력
// 소멸자: virtual, "Printer destructor" 출력
class Printer : public OutputDevice {
public:
    Printer() {
        std::cout << "Printer constructor" << std::endl;
    }
    virtual ~Printer() {
        std::cout << "Printer destructor" << std::endl;
    }
};
