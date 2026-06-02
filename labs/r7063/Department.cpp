#include "Department.hpp"

// TODO: 아래 함수들을 구현하세요.
// 주의: 기본 매개변수(= nullptr)는 헤더(Department.hpp)에 이미 선언되었습니다.
//       이 파일에서 다시 쓰면 컴파일 오류입니다. 구현부에서는 생략하세요.

Department::Department(const std::string& name, std::shared_ptr<Faculty> faculty) : name{name},  faculty{faculty} {
    // 힌트: 멤버 초기화 리스트 사용 → : name(name), faculty(faculty) {}
}

void Department::setFaculty(std::shared_ptr<Faculty> f) {
    faculty = f;
}

const std::string& Department::getName() const {
    return name;
}

std::shared_ptr<const Faculty> Department::getFaculty() const {
    return faculty; // TODO: faculty 멤버를 반환하세요
}
