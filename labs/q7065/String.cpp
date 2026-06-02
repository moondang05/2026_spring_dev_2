#include "String.h"
#include <cstring>
#include <iostream>

// static 멤버 변수 정의 (헤더에 선언만, .cpp에 반드시 정의)
// int String::count_ = 0;

int String::count_ = 0;

// TODO: 아래 멤버 함수들을 구현하세요.
//
// 생성자/소멸자에서 count_ 를 갱신하고 메시지를 출력해야 합니다:

//   기본 생성자  → "Default Constructor\n# of String object: N\n"
String::String()
{
    this->count_ = count_;
    std::cout << "Default Constructor\n# of String object: " << count_ << "\n";
}

//   C-문자열 생성자 → "Constructor\n# of String object: N\n"
explicit String::String(const char *s)
{
    const auto& str = s;
    std::cout<<"Constructor\n# of String object: "<< str <<"\n";
}
//   복사 생성자  → "Copy Constructor\n# of String object: N\n"


//   소멸자       → "Destructor\n# of String object: N\n"  (count_ 먼저 감소)
//


// String.cpp에 아래 함수들을 구현하세요. 헤더 파일(String.h)과 테스트 코드(main.cpp)는 제공됩니다.

// 각 생성자·소멸자는 count_를 갱신하고 정해진 메시지를 출력해야 합니다. 소멸자는 count_를 먼저 감소시킨 후 출력합니다.

// String() — 빈 문자열 생성. "Default Constructor\n# of String object: N\n" 출력
// explicit String(const char* s) — C-문자열로부터 생성. "Constructor\n# of String object: N\n" 출력
// ~String() noexcept — 동적 메모리 해제. "Destructor\n# of String object: N\n" 출력
// String(const String& s) noexcept — 깊은 복사(deep copy). "Copy Constructor\n# of String object: N\n" 출력
// const char* data() const — 내부 C-문자열 포인터 반환
// bool empty() const — 길이가 0이면 true
// size_t size() const — 문자열 길이 반환 ('\0' 미포함)
// String& append(const String& str) — str을 현재 문자열 뒤에 이어붙임
// String& append(const char* str) — C-문자열을 뒤에 이어붙임

// 동적 메모리는 new[] 로 할당하고 delete[] 로 해제하세요.
