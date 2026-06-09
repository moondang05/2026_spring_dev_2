#include "board_util.h"
#include <iostream>

void print_board() {
    const auto& b = get_board();
    for (const auto& row : b) {
        for (int i = 0; i < (int)row.size(); ++i) {
            if (i > 0) std::cout << ' ';
            std::cout << (row[i] == 0 ? "\u25a1" : "\u25a0");
        }
        std::cout << '\n';
    }
}

int main() {
    init_board();
    int cmd;
    while (std::cin >> cmd && cmd != 0) {
        if (cmd == 1) {
            print_board();
        } else if (cmd == 2) {
            std::cout << "Full lines: " << count_full_lines() << '\n';
        } else if (cmd == 3) {
            remove_full_lines();
            print_board();
        } else if (cmd == 4) {
            auto h = get_heights();
            std::cout << "Heights:";
            for (int v : h) std::cout << ' ' << v;
            std::cout << '\n';
        } else if (cmd == 5) {
            std::cout << "Empty cells: " << count_empty() << '\n';
        }
    }
    return 0;
}
