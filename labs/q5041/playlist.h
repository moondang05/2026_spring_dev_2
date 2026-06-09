#pragma once

// playlist.cpp 에 구현하세요.
// 재생 목록은 playlist.cpp 내부의 static 변수로 관리됩니다.
void queue_song(int song_id);
bool is_queued(int song_id);
void dequeue_song(int song_id);
void print_playlist();
