#pragma once

#include <iostream>
template <typename T>
class my_unique_ptr
{
public:
    my_unique_ptr() = default;

    explicit my_unique_ptr(T *ptr) : // ptr_(ptr) 이런 식으로 초기화하는 대신, 생성자 본문에서 ptr을 ptr_에 할당하고 ptr을 nullptr로 설정하여 소유권이 이동했음을 명확히 나타내는 방식으로 구현할 수 있습니다.
    {
        // TODO: ptr을 이 객체가 소유하도록 저장하세요.
        ptr_ = ptr;
        ptr = nullptr; // 소유권을 가져왔으므로 원래 포인터는 nullptr로 설정하여 소유권이 이동했음을 나타냅니다.
    }

    ~my_unique_ptr()
    {
        // TODO: 소유 중인 객체가 있다면 delete로 해제하세요.
        delete ptr_;
    }

    my_unique_ptr(const my_unique_ptr &) = delete;
    
    my_unique_ptr &operator=(const my_unique_ptr &) = delete;

    my_unique_ptr(my_unique_ptr &&other) noexcept
    {
        // TODO: other의 소유권을 가져오고, other는 nullptr 상태로 만드세요.
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    my_unique_ptr &operator=(my_unique_ptr &&other) noexcept
    {
        if (this != &other) {
            my_unique_ptr temp(std::move(other));
            std::swap(ptr_, temp.ptr_);
        }
        return *this;
    }
    // 위의 구현은 예외 안전성을 보장합니다. temp 객체가 소유권을 가져오고, std::swap으로 ptr_과 temp.ptr_을 교환하여 기존 소유 객체를 안전하게 해제합니다. temp가 범위를 벗어나면 기존 소유 객체가 자동으로 해제됩니다.
    // 아래의 구현은 예외 안전성을 보장하지 않습니다. delete로 기존 소유 객체를 해제한 후, other의 소유권을 가져오는데, 이 과정에서 예외가 발생할 경우, this 객체는 nullptr 상태가 되어버립니다. 따라서 위의 구현이 더 안전한 방법입니다.
    // my_unique_ptr &operator=(my_unique_ptr &&other) noexcept
    // {
    //     if (this != &other) {
    //         delete ptr_;
    //         ptr_ = other.ptr_;
    //         other.ptr_ = nullptr;
    //     }
    //     return *this;
    // }

    T *get() const
    {
        // TODO: 소유 중인 원시 포인터를 반환하세요.
        return ptr_;
    }

    T &operator*() const
    {
        // TODO: 포인터가 가리키는 객체를 참조로 반환하세요.
        return *get();
    }

    T *operator->() const
    {
        // TODO: 멤버 접근을 위해 원시 포인터를 반환하세요.
        return get();
    }

    explicit operator bool() const
    {
        // TODO: nullptr이 아니면 true를 반환하세요.
        return ptr_ != nullptr;
    }

private:
    T *ptr_ = nullptr;
};
