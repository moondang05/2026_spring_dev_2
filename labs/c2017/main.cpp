#include <iostream>
#include <memory>
#include <tuple>
#include <string>
using namespace std;
auto sum(int a, int b){
    return tuple{"sum: ", a + b};
}

int main() {
    /*하나만 만들어져야함(2개가 되는 순간 에러 발생.
      따라서 호출할 때 get()로 포인터를 넘겨줘야
      파라미터가 두개가 되는 것을 방지할 수 있음)*/
    auto pa = make_unique<int>(1);  
    auto pb = make_unique<int>(2);

    cout << *pa << ", " << *pb << endl;
    auto my_swap = [ ] (auto a, auto b) { auto temp = *a; *a = *b; *b=temp;};
    my_swap(pa.get(), pb.get());
    cout << "a: " << *pa << ", b: " << *pb << endl;

    auto [label, result] = sum(*pa, *pb);
    cout << label << result << endl;

    return 0;
}