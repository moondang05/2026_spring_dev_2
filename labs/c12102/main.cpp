#include "my_vector.h"

#include <iostream>
#include <print>
#include <ranges>
#include <string>

// std::ranges::input_range 제약을 만족하는 어떤 범위든 받아 출력한다.
// my_vector 가 begin()/end() 를 제공하므로 함께 사용할 수 있다.
template <std::ranges::input_range R>
void print_values(R &&values)
{
    bool first = true;
    for (const auto &val : values)
    {
        if (!first)
        {
            std::print(" ");
        }
        std::print("{}", val);
        first = false;
    }
    std::println("");
}

int main()
{
    std::string mode;
    if (!(std::cin >> mode))
    {
        mode = "basic";
    }

    if (mode == "basic")
    {
        // CTAD: <int> 를 명시하지 않아도 컴파일러가 추론한다.
        my_vector values = {1, 2, 3, 4, 5};
        my_vector copied(values);
        copied[4] = 10;

        print_values(values);
        print_values(copied);
    }
    else if (mode == "const")
    {
        // const 객체에서도 operator[] 로 원소를 읽을 수 있어야 한다.
        const my_vector<std::string> words = {std::string("template"), std::string("class")};
        std::println("{} {} {}", words.size(), words[0], words[1]);
    }
    else if (mode == "double")
    {
        my_vector<double> numbers = {1.5, 2.25};
        numbers[0] = 3.5;
        std::println("{} {}", numbers.size(), numbers[0] + numbers[1]);
    }
    else if (mode == "modern")
    {
        // emplace_back (가변 인자 템플릿 + 완벽한 전달) 와
        // 범위 기반 for (Deducing This 의 begin/end) 시연.
        my_vector<int> v;
        v.emplace_back(7);
        v.emplace_back(8);
        v.emplace_back(9);
        print_values(v);
        std::println("{}", v.size());
    }
}
