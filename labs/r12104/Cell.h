#pragma once

#include <concepts>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

// [제공 파일 — 수정 금지]
//
// std::variant 로 다시 짓는 Cell 클래스.
//
//   * Value 는 std::string / int / double 중 하나를 담는 타입 안전 union.
//   * 단일 템플릿 생성자가 Value 로 변환 가능한 임의의 인자를 받는다.
//     - !same_as<U, Cell> 로 자기 자신을 복사 생성자로 가로채지 않도록 차단.
//     - !same_as<U, bool> 로 bool → int 암묵적 변환이 숫자 셀로 둔갑하지
//       않도록 차단 (변수는 변수, 진리값은 진리값).
//   * value() 는 const 참조로 내부 variant 를 노출하므로, 채점기와 Excel
//     은 std::visit 으로 안전하게 분기한다.
class Cell {
public:
    using Value = std::variant<std::string, int, double>;

    Cell() = default;

    template <class T>
        requires (!std::same_as<std::remove_cvref_t<T>, Cell>
               && !std::same_as<std::remove_cvref_t<T>, bool>
               && std::constructible_from<Value, T&&>)
    Cell(T&& v) : value_(std::forward<T>(v)) {}

    [[nodiscard]] const Value& value() const noexcept { return value_; }

private:
    Value value_{};
};
