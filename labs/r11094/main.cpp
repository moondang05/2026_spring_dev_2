#include <iostream>
#include <memory>

#include "LCD_Monitor.h"
#include "LED_Monitor.h"

int main() {
    {
        Monitor monitor;
        monitor.out();              // 
    }

    std::cout << "--------------------------\n";

    {
        Monitor* monitor = new LED_Monitor();
        monitor->out();
        delete monitor;             // 자식 클래스 소멸하고 그다음 부모 클래스 까지 소멸 시켜야한다~
    }

    std::cout << "--------------------------\n";

    {
        std::unique_ptr<OutputDevice> monitor = std::make_unique<LCD_Monitor>();
        monitor->out();             // 왼쪽은 추상적(부모쪽 큰 틀 형태/OutputDevice), 오른쪽은 구체적(자식들 세부적 구조 내용/moniter, LED..., LCD...)
    }
}
