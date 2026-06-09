#pragma once
#include <vector>

void init_board();
const std::vector<std::vector<int>>& get_board();

int count_full_lines();
void remove_full_lines();
std::vector<int> get_heights();
int count_empty();
