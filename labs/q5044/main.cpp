#include "contest.h"
#include <iostream>
#include <string>

// main 함수는 미리 작성되어 있습니다. 수정하지 마세요.
// contest.cpp 에 다섯 함수를 구현하세요.
//
// 입력 형식:
//   q                            → 명령 수
//   JOIN    <name> <score> <solved> → 참가자 등록 (이미 있으면 덮어씀)
//   QUIT    <name>                  → 참가자 탈퇴 (없으면 무시)
//   SCORE   <name> <score> <solved> → 점수·해결 수 갱신 (등록된 참가자만)
//   QUALIFY <cutoff>                → cutoff 이상 참가자 이름 오름차순 출력 (없으면 NONE)
//   PRINT                           → 전체 순위표 이름 오름차순 출력 (이름 점수 해결수)

int main() {
    int q;
    std::cin >> q;
    while (q--) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "JOIN") {
            Player p;
            std::cin >> p.name >> p.score >> p.solved;
            join(p);
        } else if (cmd == "QUIT") {
            std::string name;
            std::cin >> name;
            quit(name);
        } else if (cmd == "SCORE") {
            std::string name; int score, solved;
            std::cin >> name >> score >> solved;
            update(name, score, solved);
        } else if (cmd == "QUALIFY") {
            int cutoff;
            std::cin >> cutoff;
            auto list = qualifiers(cutoff);
            if (list.empty()) std::cout << "NONE\n";
            else for (const auto& n : list) std::cout << n << '\n';
        } else {
            print_board();
        }
    }
    return 0;
}
