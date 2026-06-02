#pragma once
#include "Monitor.h"

// TODO: LED_Monitor 클래스를 구현하세요 (Monitor를 public 상속).
// 생성자: "LED_Monitor constructor" 출력
// 소멸자: override, "LED_Monitor destructor" 출력
class LED_Monitor : public Monitor
{
public:
    LED_Monitor()
    {
        cout << "LED_Monitor constructor" << endl;
    }
    ~LED_Monitor() override
    {
        cout << "LED_Monitor destructor" << endl;
    }
};
