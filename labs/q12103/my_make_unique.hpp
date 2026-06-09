#pragma once

#include "my_unique_ptr.hpp"

#include <utility>

template <typename T, typename... Args>
my_unique_ptr<T> my_make_unique(Args&&... args) {
    // TODO: new T(...)로 객체를 만들고 my_unique_ptr<T>로 감싸서 반환하세요.
    // 힌트: std::forward<Args>(args)... 를 사용하면 lvalue/rvalue 성질이 보존됩니다.
    return my_unique_ptr<T>(new T(std::forward<Args>(args)...));
}