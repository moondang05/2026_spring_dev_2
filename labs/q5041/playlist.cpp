#include "playlist.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <ranges>

// TODO: 아래 네 함수를 구현하세요.
// 재생 목록은 아래 static 변수로 관리합니다. 함수 파라미터로 전달하지 않습니다.
static std::vector<int> playlist;

void queue_song(int song_id)
{
    // 재생 목록 끝에 song_id 추가
    playlist.push_back(song_id);
}

bool is_queued(int song_id)
{
    // song_id가 재생 목록에 있으면 true 반환

//-------------------------(평소의 방식)--------------------------//

    // for (auto i : playlist)
    //     if (i == song_id)
    //         return true;
    // 
    // return false;


//-----------------------(보기 좋은 방식)--------------------------//

    auto it = std::ranges::find(playlist, song_id);
    return it != playlist.end();

        // 끝 위치가 아니라면(찾았다면) true를 반환!

        /* 위의 return문에서 true나 false값이 이미 반환됬기에
        추가로 return false; 를 달 필요 X, unreachable Code가 됨*/

//-----------------------(교수님 방식)--------------------------//

    return std::ranges::find(playlist, song_id) != playlist.end();
}

void dequeue_song(int song_id)
{
    // 재생 목록에서 song_id가 처음 등장하는 항목 제거 (없으면 아무 것도 하지 않음)

    //-------------------------(평소의 방식)--------------------------//

    // for (int i=0; i<playlist.size(); i++)
    // {
    //     if (playlist[i] == song_id)
    //     {
    //         playlist.erase(playlist.begin() + i);
    //         break;
    //     }

    // }

    //-----------------------(보기 좋은 방식)--------------------------//
    auto target = std::ranges::find(playlist, song_id);
    if (target != playlist.end())
        playlist.erase(target);
}

void print_playlist()
{
    // 재생 목록의 곡 ID를 한 줄에 하나씩 출력
    for (const auto& i : playlist)
        // 메모리 복사 방지(const) 및 수정 불가(안전성) 보장
        std::cout << i << '\n';
}
