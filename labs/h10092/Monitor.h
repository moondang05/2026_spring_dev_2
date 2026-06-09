#pragma once
#include "OutputDevice.h"
using namespace std;

// TODO: Monitor 클래스를 구현하세요 (OutputDevice를 public 상속).
// 생성자: "Monitor constructor" 출력
// 소멸자: virtual, "Monitor destructor" 출력
class Monitor : public OutputDevice
{
public:
    Monitor()
    {
        cout << "Monitor constructor" << endl;
    }
    ~Monitor() override
    {
        cout << "Monitor destructor" << endl;
    }
};
