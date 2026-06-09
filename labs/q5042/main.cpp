#include "marathon.h"
#include <iostream>
#include <iomanip>
#include <string>

// main 함수는 미리 작성되어 있습니다. 수정하지 마세요.
// marathon.cpp 에 여덟 함수를 구현하세요.
//
// 명령 형식 (EOF 까지 반복):
//   ADD name time age   → 참가자 추가
//   REMOVE name         → 이름으로 첫 매칭 제거 (없으면 무시)
//   UPDATE name new_time → 이름으로 기록 수정 (없으면 무시)
//   FIND name           → "name time age" 출력, 중복 있으면 모두 출력, 없으면 NOT FOUND
//   STATS               → 합계 / 평균(소수점 둘째자리) / 최고 기록 / 최저 기록 출력

int main() {
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "ADD") {
            Runner r;
            std::cin >> r.name >> r.time >> r.age;
            add_runner(r);
        } else if (cmd == "REMOVE") {
            std::string name;
            std::cin >> name;
            remove_runner(name);
        } else if (cmd == "UPDATE") {
            std::string name; int t;
            std::cin >> name >> t;
            update_time(name, t);
        } else if (cmd == "FIND") {
            std::string name;
            std::cin >> name;
            print_runner(name);
        } else if (cmd == "STATS") {
            std::cout << total_time() << '\n';
            std::cout << std::fixed << std::setprecision(2) << avg_time() << '\n';
            std::cout << best_time() << '\n';
            std::cout << worst_time() << '\n';
        }
    }
    return 0;
}
