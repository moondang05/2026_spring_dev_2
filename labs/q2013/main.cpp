#include <iostream>
using namespace std;

// 다른 파일(pointer.cpp)에 있는 함수를 쓰겠다고 선언
void update(int* a, int* b);

int main() {
    int a, b;
    int* pa = &a, * pb = &b;
    cin >> a >> b;
    update(pa, pb);
    cout << a << " " << b << endl;
    return 0;
}