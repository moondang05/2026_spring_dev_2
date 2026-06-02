#pragma once
#include <string>
#include <vector>

struct Player {
    std::string name;  // 참가자 이름
    int score;         // 현재 점수
    int solved;        // 해결한 문제 수
};

// contest.cpp 에 구현하세요.
// 순위표는 contest.cpp 내부의 static 변수로 관리됩니다.
void join(const Player& p);
void quit(const std::string& name);
void update(const std::string& name, int score, int solved);
std::vector<std::string> qualifiers(int cutoff);
void print_board();
