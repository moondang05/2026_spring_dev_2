#include "movie.h"
#include <iostream>
#include <string>

int main() {
    MovieDatabase db;

    // TODO: 영화 제목을 한 줄씩 입력받으세요.
    std::string title;
    std::string genre;
    std::string rates;
    // TODO: 제목이 "q"이면 입력을 종료하고 요약을 출력하세요.
    while (title == "q") {
        std::getline(std::cin, title);
    // TODO: 각 영화에 대해 장르(Action, Drama, SciFi)와 별점 문자열(예: ★★★★☆)을 읽어
        std::cin >> genre;
        std::cin >> rates;
    }

    // TODO: db.addRating(...)으로 누적한 뒤 마지막에 db.printSummary()를 호출하세요.

    return 0;
}
