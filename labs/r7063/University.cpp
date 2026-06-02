#include "University.hpp"
#include <iostream>
#include <print>

// TODO: 아래 함수들을 구현하세요.

University::University(const std::string& name) :name{name} {
    // 힌트: 멤버 초기화 리스트 사용 → : name(name) {}
    // departments는 vector 기본 생성자로 빈 상태가 자동 초기화됩니다.
}

void University::addDepartment(const Department& dept) {
    departments.push_back/*복사 같은거다*/(dept);
    // departments.emplace_back(dept);


    // TODO: vector에 dept를 추가하세요.
    // 힌트: departments.push_back(dept);
}

void University::printInfo() const {
    // 출력 형식:
    // "University Name: <name>\n"
    // "Number of Departments: <departments.size()>\n"
    // 각 학과마다:
    //   "\n"  (빈 줄)
    //   "Department Name: <name>\n"
    //   faculty가 nullptr:  "Faculty Name: N/A\n" + "Number of Faculty Members: N/A\n"
    //   faculty가 있음:     "Faculty Name: <name>\n" + "Number of Faculty Members: <num>\n"
    // 힙트: auto f = dept.getFaculty(); if (f) { ... } else { ... }
    std::cout<<"University Name: "<<name<<'\n';
    std::cout<<"Number of Departments: "<<departments.size()<<'\n';

    // auto f = departments.getFaculty();



    for (auto d: departments) {
        std::print("Department Name: {}\n", d.getName());
        auto f = d.getFaculty();
        if(f) {
            std::print("Faculty Name: {}\n", f->getName());
            std::print("Number of Faculty Members : {}\n", f->getNumMembers());
        }
        else {
            std::print("Faculty Name: N/A\n");
            std::print("Number of Faculty Members : N/A\n");
        }
        std::print("\n");
    }
}
