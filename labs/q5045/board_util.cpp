#include "board_util.h"
#include <vector>
#include <algorithm>
#include <ranges>

static std::vector<std::vector<int>> board;

// 힌트: is_full 헬퍼 람다를 여러 함수에서 재사용할 수 있습니다.
static auto is_full = [](const std::vector<int>& row) {
    return std::ranges::all_of(row, [](int cell) { return cell == 1; });
};

void init_board() {
    board = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1}
    };
}

const std::vector<std::vector<int>>& get_board() {
    return board;
}

int count_full_lines() {
    // TODO: 모든 칸이 1인 행의 수를 반환하세요.
    // std::ranges::count_if + std::ranges::all_of 사용 권장
    /*
    // [이전 코드 형태]
    return std::ranges::count_if(board, [](const std::vector<int>& row) {
        return std::ranges::all_of(row, [](int cell) { return cell == 1; });
    });
    return 0;
    */
    
    // [모던 C++ 방식] 공통 헬퍼 람다(is_full)를 활용한 직관적인 순회
    return std::ranges::count_if(board, is_full);
}

void remove_full_lines() {
    // TODO: 완성된 행을 제거하고, 제거된 수만큼 빈 행을 위에 삽입하세요.
    /*
    // [이전 코드 형태 - 오답: 줄을 채우지 않음]
    board.erase(std::ranges::remove_if(board, [](const std::vector<int>& row) {
        return std::ranges::all_of(row, [](int cell) { return cell == 1; });
    }).begin(), board.end());
    */
    
    // [모던 C++ 방식] C++20 std::erase_if의 반환값(지워진 개수)을 적극 활용
    int cols = board.empty() ? 0 : board[0].size();
    int removed = std::erase_if(board, is_full);
    board.insert(board.begin(), removed, std::vector<int>(cols, 0));
}

std::vector<int> get_heights() {
    // TODO: 각 열에서 블록이 쌓인 높이를 반환하세요.
    /*
    // [이전 코드 형태 - 오답: 높이 무조건 0 리턴]
    int cols = board.empty() ? 0 : (int)board[0].size();
    return std::vector<int>(cols, 0);
    // [C++20 초기 형태 - vector 생성자로 변환]
    // auto heights = std::views::iota(0, cols) | std::views::transform([...]);
    // return std::vector<int>(heights.begin(), heights.end());
    */
   
    // [C++23 방식] std::ranges::to<std::vector>()를 파이프라인의 끝에 사용하여 직관적으로 반환
    int cols = board.empty() ? 0 : (int)board[0].size();
    return std::views::iota(0, cols) | std::views::transform([&](int c) {
        auto it = std::ranges::find_if(board, [c](const std::vector<int>& row) {
            return row[c] == 1;
        });
        return it == board.end() ? 0 : static_cast<int>(std::ranges::distance(it, board.end()));
    }) | std::ranges::to<std::vector>();
}

int count_empty() {
    // TODO: 보드 전체에서 빈 칸(0)의 수를 반환하세요.
    /*
    // [이전 코드 형태 - fold_left 기반 누적 계산]
    return std::ranges::fold_left(board, 0, [](int sum, const std::vector<int>& row) {
        return sum + std::ranges::count(row, 0);
    });
    return 0;
    */
    
    // [C++20 방식] views::join을 활용하여 2차원 컨테이너를 1차원처럼 펼쳐 간결하게 해결
    auto flat_board = board | std::views::join;
    return std::ranges::count(flat_board, 0);
}
