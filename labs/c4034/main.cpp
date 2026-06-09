#include <iostream>
#include <random>
#include <string_view>
using namespace std;

enum class Hand
{
    Rock = 0,
    Scissors = 1,
    Paper = 2
};

const char *hand_to_text(Hand hand)
{
    switch (hand)
    {
    case Hand::Rock:
        return "묵";
    case Hand::Scissors:
        return "찌";
    case Hand::Paper:
        return "빠";
    default:
        return "?";
    }
}

int main()
{
    int player_code;
    cin >> player_code;

    mt19937 rng(20260324u);
    const Hand computer = static_cast<Hand>(rng() % 3);
    const Hand player = static_cast<Hand>(player_code);

    cout << "컴퓨터: " << hand_to_text(computer) << '\n';
    cout << "플레이어: " << hand_to_text(player) << '\n';

// 문자열 리터럴을 비교 연산자로 사용하면 번지수 비교이기 때문에 오류가 납니다. (string_view 사용으로 안전하게 해결)
    if (string_view(hand_to_text(player)) == "?")
        return 0;

//정수형 단위에서 구간을 설정하여 제한하는 것이 훨씬 안전성이 뛰어나다!
    if (player_code < 0 || player_code > 2)
        return 0;

    cout << "결과: ";

    int res = (player_code - static_cast<int>(computer) + 3) % 3;
    if (res == 0)
        cout << "비김" << endl;
    else if (res == 1)
        cout << "컴퓨터 승" << endl;
    else if (res == 2)
        cout << "플레이어 승" << endl;

    // switch (computer) {
    //     // TODO: 고정 seed 20260324 로 만든 mt19937 의 첫 난수 % 3 값을 컴퓨터 손으로 사용합니다.
    //     // TODO: computer 와 player 의 조합에 따라 결과를 출력하세요.
    //     case Hand::Rock:
    //         if (player == Hand::Rock) {
    //             cout << "비김" << endl;
    //         } else if (player == Hand::Paper)
    //         {
    //             cout << "플레이어 승" << endl;
    //         } else {
    //             cout << "컴퓨터 승" << endl;
    //         }
    //         break;

    //     case Hand::Scissors:
    //         if (player == Hand::Rock) {
    //             cout << "플레이어 승" << endl;
    //         } else if (player == Hand::Paper)
    //         {
    //             cout << "컴퓨터 승" << endl;
    //         } else {
    //             cout << "비김" << endl;
    //         }
    //         break;

    //     case Hand::Paper:
    //         if (player == Hand::Rock) {
    //             cout << "컴퓨터 승" << endl;
    //         } else if (player == Hand::Paper)
    //         {
    //             cout << "비김" << endl;
    //         } else {
    //             cout << "플레이어 승" << endl;
    //         }
    //         break;

    //     default:
    //         return 0;
    //         break;
    // }

    return 0;
}

/*
걸리는 점들

1. switch 케이스 내 조건문에서 나머지를 뭉뜽그려 else로 처리해도 되는가?
   만약 플레이어가 0, 1, 2를 제외한 무언가를 입력했다면?
        ->이를 방지하기 위한 버퍼를 넣어야 한다. 물론 handtotext에 들어있으나
        그렇다고 해서 그게 결과까지 나오는걸 막아줄 수는 없다.

2. 만약 랜덤 시드를 고정 하지 않았다고 가정 했을 때 지금 형태는 잘 작동하긴 하지만
   사실 이는 모든 경우의 수를 직접 일일히 작성한 꼴이다. 좀 더 나은 방법은 없을까?
        ->가위바위보는 승, 패, 비김으로 결과가 고정되는데 

3. switch라는 함수에서 소괄호 자리에 들어가는 그 대상은 어떻게 작용하는 것인가.
    -> 검토할 대상을 넣는 자리.

4. player와 computer는 그래서 변수의 타입이 어떻게 되는건가.
*/