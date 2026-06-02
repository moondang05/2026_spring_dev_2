#include <iostream>

// TODO: 참조 변수(reference variable)를 파라미터로 사용하는
// TODO: void my_swap(int& a, int& b) 함수를 구현하세요.

void my_swap(int& a, int& b) {
    // TODO: 임시 변수를 사용하여 두 값을 서로 교환하세요.
    int temp = a; // a의 값을 임시 변수에 저장
    a = b;        // b의 값을 a에 할당
    b = temp;     // 임시 변수의 값을 b에 할당
    return;
}


int main() {
    int m, n;
    std::cin >> m >> n;
    my_swap(m, n);
    std::cout << m << " " << n;
}
