#include <iostream>
#include "tetris.h"

using namespace std;

int main() {
    GameState state;

    // 1. 게임 상태 초기화 (보드 생성 및 기본 블록 세팅)
    init_game(state);

    // 2. 초기 상태 출력
    std::cout << "--- 초기 테트리스 보드 ---\n";
    std::cout << board_to_string(state) << "\n";

    // 3. 구조체 값을 직접 바꿔서 출력 테스트 (테스트용)
    state.block_x = 2;   // x (가로) 좌표 이동
    state.block_y = 5;   // y (세로) 좌표 이동 (아래로)
    
    // 블록 모양을 'O' 모양 (2x2 네모 블록)으로 변경해보기
    state.current_block = {
        {1, 1, 0},
        {0, 1, 1}
    };

    std::cout << "--- 블록 위치/모양 변경 후 ---\n";
    std::cout << board_to_string(state) << "\n";

    return 0;
}
