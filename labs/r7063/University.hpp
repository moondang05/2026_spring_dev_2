#ifndef UNIVERSITY_HPP
#define UNIVERSITY_HPP

#include <string>
#include <vector>
#include "Department.hpp"

// Rule of Zero: std::string과 std::vector<Department>가
// 자체적으로 복사/소멸을 처리하므로 복사 생성자/대입 연산자/소멸자를 직접 작성하지 않습니다.
class University {
public:
    explicit University(const std::string& name);
    void addDepartment(const Department& dept);
    void printInfo() const;

private:
    std::string name;
    std::vector<Department> departments;
};

#endif // UNIVERSITY_HPP
