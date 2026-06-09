#ifndef STRINGSPLITTER_H
#define STRINGSPLITTER_H

#include <string>
#include <vector>

class StringSplitter {
private:
    std::string data_;

public:
    StringSplitter(const std::string& str);

    // 메서드 체이닝: *this 를 반환하여 .trim().replace...().split() 형태로 연결
    StringSplitter& trim();
    StringSplitter& replaceSubstring(const std::string& from, const std::string& to);
    StringSplitter& removePunctuation();

    // 터미널 연산: 체인의 마지막에 호출하여 결과를 ���환
    std::vector<std::string> split(char delimiter) const;
};

#endif // STRINGSPLITTER_H
