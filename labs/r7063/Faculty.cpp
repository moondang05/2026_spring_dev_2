#include "Faculty.hpp"

// TODO: 아래 함수들을 구현하세요.
// 힙트: 생성자에서 멤버 초기화 리스트를 사용하세요.
//       Faculty::Faculty(const std::string& name, int numMembers) : name(name), numMembers(numMembers) {}

Faculty::Faculty(const std::string& name, int numMembers) :name{name}, numMembers{numMembers} {
}

const std::string& Faculty::getName() const {
    return name;
}

int Faculty::getNumMembers() const {
    return numMembers; 
}
