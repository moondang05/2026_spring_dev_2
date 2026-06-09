#ifndef FACULTY_HPP
#define FACULTY_HPP

#include <string>

class Faculty {
public:
    Faculty(const std::string& name, int numMembers);
    const std::string& getName() const;
    int getNumMembers() const;

private:
    std::string name;
    int numMembers;
};

#endif // FACULTY_HPP
