#include <iostream>
using namespace std;

int main() {
    int score;
    cin >> score;

    // TODO: score 값에 따라 A, B, C, D, F 중 하나를 출력하세요.
    if (score>=90) cout << "A" << endl;
    else if (score>=80) cout << "B" << endl;
    else if (score>=70) cout << "C" << endl;
    else if (score>=60) cout << "D" << endl;
    else cout << "F" << endl;
    
    
    // 90 이상은 A, 80 이상은 B, 70 이상은 C, 60 이상은 D, 그보다 작으면 F 입니다.

    return 0;
}
