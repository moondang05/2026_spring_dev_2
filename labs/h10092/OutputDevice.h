#pragma once
#include <iostream>

// TODO: OutputDevice 클래스를 구현하세요.
// 생성자: "OutputDevice constructor" 출력
// 소멸자: virtual, "OutputDevice destructor" 출력
class OutputDevice
{
public:
    OutputDevice()
    {
        std::cout << "OutputDevice constructor" << std::endl;
    }

    virtual ~OutputDevice()
    {
        std::cout << "OutputDevice destructor" << std::endl;
    }
};
