#pragma once
#include <string>

struct Runner {
    std::string name;  // 참가자 이름
    int time;          // 완주 기록 (분)
    int age;           // 나이
};

// marathon.cpp 에 구현하세요.
// 참가자 목록은 marathon.cpp 내부의 static 변수로 관리됩니다.
void add_runner(const Runner& r);               // 참가자 추가
void remove_runner(const std::string& name);    // 이름으로 첫 매칭 제거
void update_time(const std::string& name, int new_time);  // 이름으로 기록 수정
void print_runner(const std::string& name);     // 이름으로 참가자 전체 출력, 없으면 NOT FOUND
int  total_time();                              // 완주 시간 합계
double avg_time();                              // 평균 완주 시간
int  best_time();                               // 최고(최단) 기록
int  worst_time();                              // 최저(최장) 기록
