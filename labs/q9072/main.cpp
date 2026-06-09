#include <iostream>
#include "Range.hpp"

int main() {
    auto print = [](const char* label, const Range& r) {
        std::cout << label << ":";
        for (long long i : r) std::cout << " " << i;
        std::cout << "\n";
    };

    print("range(5)", Range(5));
    print("range(2, 8)", Range(2, 8));
    print("range(1, 10, 2)", Range(1, 10, 2));
    print("range(10, 0, -1)", Range(10, 0, -1));
    print("range(10, 0, -3)", Range(10, 0, -3));
    print("range(5, 5)", Range(5, 5));
    print("range(10, 0, 1)", Range(10, 0, 1));
    print("range(0, 10, -1)", Range(0, 10, -1));
    print("range(1, 10, 0)", Range(1, 10, 0));

    return 0;
}
