#include <iostream>

int main() {
    int n;
    std::cin >> n;

    // TODO: 길이 n의 정수 배열을 준비하세요.
    int arr[n];

    // TODO: n개의 정수를 입력받아 배열에 저장하세요.
    for (int i = 0; i <n; i++) {
        std::cin >> arr[i];
    }
    // TODO: 배열의 마지막 원소부터 첫 원소까지 역순으로 출력하세요.
    for (int i = n - 1; i >= 0; i--) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}