#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    // TODO: 생성자 — 멤버 초기화 목록으로 name 초기화, "Person is constructed!" 출력
    Person(string name) : name(move(name))
    {
        cout << "Person is constructed!" << endl;
    }

    // TODO: virtual 소멸자 — "Person is destructed!" 출력
    virtual ~Person()
    {
        cout << "Person is destructed!" << endl;
    }

    // TODO: "Person Name: ..." 출력
    virtual void print() const
    {
        cout << "Person Name: " << name << endl;
    }

protected:
    string name;
};

class Student : public Person
{
public:
    // TODO: 생성자 — Person과 school을 초기화 목록으로 초기화, "Student is constructed!" 출력
    Student(string name, string school)
        : Person(move(name)), school(move(school))  // member initialzed list
    {
        cout << "Student is constructed!" << endl;
    }

    // TODO: override 소멸자 — "Student is destructed!" 출력
    ~Student() override
    {
        cout << "Student is destructed!" << endl;
    }

    // TODO: Person::print() 호출 후 "School Name: ..." 출력
    void print() const override
    {
        Person::print();
        cout << "School Name: " << school << endl;
    }

private:
    string school;
};

int main()
{
    Person p1{"Park"};
    p1.print();

    Student s1{"Kim", "PNU"};
    s1.print();

    return 0;
}
