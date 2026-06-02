#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }

    int even_sum = 0;
    int odd_sum = 0;

    // TODO: values 를 range-based for 문으로 순회하세요.
    // TODO: 짝수는 even_sum, 홀수는 odd_sum 에 더하세요.
    for (int v : values) {
        if (v % 2 == 0) {
            even_sum += v;
        } else {
            odd_sum += v;
        }
    }

    std::cout << even_sum << '\n';
    std::cout << odd_sum << '\n';

    return 0;
}
