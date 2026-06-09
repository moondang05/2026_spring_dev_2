#include <memory>
#include "University.hpp"
#include "Department.hpp"
#include "Faculty.hpp"

int main() {
    auto faculty = std::make_shared<Faculty>("Computer Science", 10);
                        // 이전에 생성자를 새로 생성할 때,
                        // new와 delete를 사용하지 않을 시
                        // 메모리 누수나 오류가 자주 발생했기에
                        // 번거로운 과정을 거치지 않고 사용할 수 있도록 개편되었다.


    // int a = 5;
    // int b = a;

    // Faculty f1();
    // Faculty f2;

    // f2 = f1;

    // Faculty는 value로만 구성되어 있기에 int처럼 사용할 수 있다~

    // struct Student {};

    // Student s1;
    // Student s2;

    // s2 = s1;
    
    // std::vector<Department> v1 = {};
    // std::vector<Department> v2 = {};

    // v1 = v2;

    University univ("Pusan National University");
    univ.addDepartment(Department("Math"));
    univ.addDepartment(Department("Information and Biomedical Engineering", faculty));
    univ.addDepartment(Department("Computer Science and Engineering", faculty));

    univ.printInfo();
    return 0;
}
