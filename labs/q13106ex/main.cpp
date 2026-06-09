#include <iostream>
#include <stdexcept>
#include <vector>

#include "module.h"

using namespace std;

class MyException : public std::exception
{
public:
    MyException(const auto str) : std::exception(str) {}
};

int devide(int a, int b)
{
    if (b == 0)
    {
        throw runtime_error("Division by zero is not allowed.");
        // 생성자가 throw를 던지면
    }
    return a / b;
}

std::vector v;

int at(int i)
{
    return v[i];
}

int process(int i)
{
    try
    {
        return devide(i, 0);
    }
    catch (MyException &e)
    {
        std::cerr << "ERROR!\n";
        // throw xxxx("AAAA");
        // 중간에서 잡아주려면 계속 던저줘야함(잡으려면 책임지고 해결하던가 (내 메모리 소비하게 됨) 위로 또 넘겨줘야함)
    }
}

int main()
{
    try
    {
        cout << process(3);
        at(-1);
    }
    catch (runtime_error &r)
    {
        cout << "HAHAHA!";
    }
    catch (MyException &e)
    {
        std::cout << "HAHHAHAHA!";
    }
    // 쓰는 사람이 catch로 잡아줘야 한다.
    // 중간 과정을 걸쳐 사용시 소멸자를 호출하는 서순에 문제가 나지 않기 위해 맨 마지막인 메인에서 잡아주는게 일반적?
    return 0;
}
