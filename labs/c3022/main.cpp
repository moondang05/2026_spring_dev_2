#include <iostream>

int main() {
    int rows, cols;
    std::cin >> rows >> cols;

    // TODO: rows x cols 크기의 2차원 정수 배열을 준비하세요.
    int arr[rows][cols];
    int rowSum[rows];
    int colSum[cols];

    for (int i = 0; i < rows; i++) rowSum[i] = 0;
    for (int i = 0; i < cols; i++) colSum[i] = 0;

    // TODO: 행렬을 입력받으면서 각 행의 합과 각 열의 합을 계산하세요.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> arr[i][j];
            rowSum[i] += arr[i][j];
            colSum[j] += arr[i][j];
        }
    }

    // TODO: 첫째 줄에 행의 합, 둘째 줄에 열의 합을 출력하세요.
    for (int i = 0; i < rows; i++)
    {
        std::cout << rowSum[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cols; i++)
    {
        std::cout << colSum[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
