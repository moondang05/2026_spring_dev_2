#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <map>
#include <initializer_list>

class Phonebook {
    // map의 타입을 명확히 정의합니다.
    using contact_map = std::map<std::string, int>;
    contact_map contacts;

public:
    // contact_map::value_type = std::pair<const std::string, int>
    // std::map의 key는 항상 const입니다 (삽입 후 변경 불가).
    // value_type을 재사용하면 타입 불일치 없이 멤버 초기화 리스트(: contacts(lst))를 쓸 수 있습니다.
    using value_type = contact_map::value_type;

    Phonebook(std::initializer_list<value_type> lst);
    void print() const;

};

#endif // PHONEBOOK_HPP
