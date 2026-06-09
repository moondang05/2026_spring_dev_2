#include "playlist.h"
#include <iostream>
#include <string>

// main 함수는 미리 작성되어 있습니다. 수정하지 마세요.
// playlist.cpp 에 네 함수를 구현하세요.
//
// 입력 형식:
//   n              → 초기 재생 목록 곡 수
//   id1 id2 ...    → 초기 곡 ID (n개)
//   q              → 이후 명령 수
//   QUEUE <id>     → 재생 목록 끝에 곡 추가
//   CHECK <id>     → 곡이 있으면 YES, 없으면 NO 출력
//   SKIP  <id>     → 처음 일치하는 곡 제거 (없으면 무시)
// 모든 명령 처리 후 재생 목록을 한 줄에 하나씩 출력합니다.

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int id;
        std::cin >> id;
        queue_song(id);
    }

    int q;
    std::cin >> q;
    while (q--) {
        std::string cmd;
        int id;
        std::cin >> cmd >> id;
        if (cmd == "QUEUE") {
            queue_song(id);
        } else if (cmd == "CHECK") {
            std::cout << (is_queued(id) ? "YES" : "NO") << '\n';
        } else {
            dequeue_song(id);
        }
    }

    print_playlist();
    return 0;
}
