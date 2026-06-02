#include "Phonebook.hpp"
#include <iostream>

// TODO: 아래 두 함수를 구현하세요.
// Phonebook은 생성 후 상태가 변하지 않습니다 (print는 const 멤버 함수).

// [타입 일치 주의]
// std::map<K, V>의 value_type은 std::pair<const K, V>입니다.
// key(K)에 const가 붙는 이유: map에 삽입된 key는 변경할 수 없습니다.
//   (key가 바뀌면 map의 정렬 순서가 깨지므로 표준 라이브러리가 타입 레벨에서 방지합니다.)
//
// std::pair<std::string, int>와 std::pair<const std::string, int>는 서로 다른 타입이므로
// initializer_list의 T가 다르면 암시적 형변환이 일어나지 않습니다.
//
// 헤더(Phonebook.hpp)의 value_type이 contact_map::value_type과 정확히 일치하므로
// 멤버 초기화 리스트(: contacts(lst))를 사용할 수 있습니다.

Phonebook::Phonebook(std::initializer_list<value_type> lst) : contacts {lst}
    // 힌트: 멤버 초기화 리스트로 contacts를 직접 초기화합니다.
    //       : contacts(lst)
    // (value_type = std::pair<const std::string, int>이므로 타입이 정확히 일치합니다.)
    //
    // 또는 반복문으로 삽입해도 됩니다:
    // for (const auto& [name, num] : lst) { contacts[name] = num; }
    //   structured binding (C++17): [name, num]으로 pair를 분해합니다.
{
}

void Phonebook::print() const {
    // contacts의 모든 항목을 "이름 나이\n" 형식으로 출력하세요.
    // std::map은 키(이름)를 알파벳순으로 자동 정렬합니다.
    // 힌트: for (const auto& [name, num] : contacts) { ... }
    for (const auto& [name, num] : contacts)
    {
        std::cout << name << " " << num << std::endl;
    }
    
}
