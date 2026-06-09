#include <iostream>
#include <memory>
using namespace std;

void update(int* a, int* b);

int main() {
    unique_ptr<int> a = make_unique<int>();
    unique_ptr<int> b = make_unique<int>();

    cin >> *a >> *b;

    // TODO: 스마트 포인터가 관리하는 두 값을 update()로 갱신하세요.
    update(a.get(), b.get());
    // TODO: 갱신된 두 값을 공백 하나로 구분해 출력하세요.
    cout << *a << " " << *b <<endl;
    return 0;
}

void update(int* a, int* b) {
    // TODO: 원래 첫 번째 값을 보관한 뒤,
    // TODO: *a에는 두 수의 합을, *b에는 원래 첫 번째 값 - 원래 두 번째 값을 저장하세요.
    int temp = *a;
    *a = *a + *b;
    *b = temp - *b;
}