#include <iostream>
using namespace std;

void update(int* a, int* b) {
    // if (a == nullptr || b == nullptr) return;
    // int temp = *a;
    // *a = *a + *b;
    // *b = temp - *b; 

    if (!a) return;
    if (!b) return;

    int add = *a + *b;
    int sub = *a - *b;
    *a = add;
    *b = sub;
}
