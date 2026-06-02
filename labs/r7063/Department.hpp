#ifndef DEPARTMENT_HPP
#define DEPARTMENT_HPP

#include <memory>
#include <string>
#include "Faculty.hpp"

// Rule of Zero: std::string과 std::shared_ptr<Faculty>가
// 자체적으로 복사/소멸을 처리하므로 복사 생성자/대입 연산자/소멸자를 직접 작성하지 않습니다.
class Department {
public:
    explicit Department(const std::string& name,
                        std::shared_ptr<Faculty> faculty = nullptr);
    void setFaculty(std::shared_ptr<Faculty> faculty);
    const std::string& getName() const;
    std::shared_ptr<const Faculty> getFaculty() const;

private:
    std::string name;
    std::shared_ptr<Faculty> faculty;
};

#endif // DEPARTMENT_HPP
