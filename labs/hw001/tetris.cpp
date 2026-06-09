#include "tetris.h"
#include <iomanip>

void init_game(GameState& state) {
    state = GameState{};  // block_x=4, block_y=0, running=true는 기본값으로 채워짐
    // TODO: board를 BOARD_HEIGHT행 × BOARD_WIDTH열, 모두 '.'으로 초기화
    // TODO: current_block = {{1, 1, 1, 1}}  (1행 4열 I 블록)

    state.board = std::vector<std::vector<char>> (BOARD_HEIGHT,std::vector<char>(BOARD_WIDTH,'.'));
    state.current_block = {{1, 1, 1, 1}};
    
    // state.board.assign(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, '.'));
    // state.current_block = {{1, 1, 1, 1}};

}

std::string board_to_string(const GameState& state) {
    // TODO: state.board의 복사본을 만든다
    // TODO: current_block을 [y][x] 순서로 순회하며 복사본에 '#'을 찍는다
    //       board_x = block_x + x,  board_y = block_y + y
    //       보드 범위를 벗어난 칸은 건너뛴다
    // TODO: 복사본을 "+----------+\n| ... |\n" 형식의 문자열로 변환해 반환한다

    // --- 여기서부터 수정본 (위의 코드는 지우지 않고 그대로 두었습니다) ---

    
    auto copy = state.board;
    // 1. 블록의 모양(크기)만큼 반복해야 합니다.
    for (int y = 0; y < state.current_block.size(); ++y) {
        for (int x = 0; x < state.current_block[y].size(); ++x) {
            if (state.current_block[y][x] == 0) continue; // 빈 칸 건너뛰기
            
            const int board_x = state.block_x + x;
            const int board_y = state.block_y + y;
            
            // 보드 범위를 벗어나는지 확인 후, 복사본(copy)의 좌표에 '#' 찍기
            if (board_y >= 0 && board_y < BOARD_HEIGHT &&
                board_x >= 0 && board_x < BOARD_WIDTH) {
                copy[board_y][board_x] = '#';
            }
        }
    }

    // 2. 복사본을 문자열로 예쁘게 조립해서 반환합니다.
    std::ostringstream out;
    out << "+----------+\n";
    for (const auto& row : copy) {
        out << '|';
        for (char cell : row) {
            out << cell;
        }
        out << "|\n";
    }
    out << "+----------+\n";
    
    return out.str();
}