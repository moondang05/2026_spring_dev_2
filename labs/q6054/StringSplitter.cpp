#include "StringSplitter.h"
#include <cctype>
#include <sstream>

// TODO: 아래 함수들을 구현하세요.
// trim(), replaceSubstring(), removePunctuation() 은 *this 를 반환하여
// 메서드 체이닝을 가능하게 합니다.

StringSplitter::StringSplitter(const std::string &str): data_{str}
{
    // data_ 에 입력 문자열을 저장합니다.
    // data_ = str;  // 기존 방식(만약 지금 함수에서 data_가 사용되고 있다면 'this->data_'활용)
}

StringSplitter &StringSplitter::trim()
{
    // data_ 의 앞뒤 공백을 제거합니다.
    // 힌트: find_first_not_of(' ') 와 find_last_not_of(' ') 사용
    // 반드시 return *this; 로 끝내세요.
    auto start = data_.find_first_not_of(' '); // 공백이 없는 처음의 위치를 반환
    auto end = data_.find_last_not_of(' ');    // 공백이 없는 마지막의 위치를 반환

    auto length = end - start + 1;

    data_ = data_.substr(start, length);

    return *this;
}

StringSplitter &StringSplitter::replaceSubstring(const std::string &from,
                                                 const std::string &to)
{
    // data_ 에서 from 을 찾아 to 로 교체합니다 (첫 번째 등장만).
    // 힌트: data_.find(from) 으로 위치를 찾고
    //       data_.replace(pos, from.length(), to) 로 교체
    // from 이 없으면 아무 것도 하지 않습니다.
    auto start = data_.find(from);
    if (start != std::string::npos)data_.replace(start, from.length(), to);
        // npos는 특수 상수로 no position(위치 없음)을 나타냄
    return *this;
}

StringSplitter &StringSplitter::removePunctuation()
{
    // data_ 에서 구두점 문자를 모두 제거합니다.
    // 힌트: std::ispunct(c) 가 true 인 문자를 제거
    //       erase-remove 관용구 또는 std::erase_if(data_, ::ispunct) 사용
    
    // C++23 방식
    std::erase_if(data_, ::ispunct);

    // 기존 방식
    // std::erase_if(data_, [](unsigned char c) {return std::ispunct(c);});
    return *this;
}

std::vector<std::string> StringSplitter::split(char delimiter) const
{
    // data_ 를 delimiter 기준으로 나눠 벡터로 반환합니다.
    // 빈 토큰은 포함하지 않습니다.
    // 힌트: std::istringstream 으로 getline(iss, token, delimiter) 반복
    std::vector<std::string> ret;
    auto iss = std::istringstream(data_);    // istringstream 공부하기

    std::string str;
    while (std::getline(iss,str,delimiter))  // getline 톺아보기(vs cin)
    {
        if(str.empty()) continue;  // 빈 토큰은 건너뛰기
        ret.push_back(str);
    }
    
    return ret;
}
