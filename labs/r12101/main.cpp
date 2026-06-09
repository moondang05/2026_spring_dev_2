// =========================================================================
// 같은 함수 my_accumulate 를 두 가지 스타일로 호출하여 결과를 비교합니다.
//
//   - 위쪽 블록: [C++17] 현재 방식  ::  my_accumulate(begin, end, init)
//   - 아래쪽 블록: [C++20/23] 최신 방식 ::  modern::my_accumulate(range, init)
//
// 학생은 두 헤더 (my_accumulate.h, my_accumulate_modern.h) 를 모두
// 구현해야 합니다. 이 파일은 제출 대상이 아니며 수정하지 않습니다.
// =========================================================================

#include "my_accumulate.h"
#include "my_accumulate_modern.h"

#include <iostream>
#include <list>
#include <ranges>
#include <string>
#include <vector>

int main() {
    using namespace std::string_literals;

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<double> nums = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::list<std::string> words = {"hello", ",", "world!"};

    // ------------------------------------------------------------------
    // [C++17] 반복자 두 개를 직접 넘기는 전통적인 호출 방식
    // ------------------------------------------------------------------
    std::cout << "[C++17]\n";
    std::cout << "sum(int):    " << my_accumulate(vec.cbegin(), vec.cend(), 0) << '\n';
    std::cout << "sum(double): " << my_accumulate(nums.cbegin(), nums.cend(), 0.0) << '\n';
    std::cout << "join(str):   " << my_accumulate(words.cbegin(), words.cend(), ""s) << '\n';

    // ------------------------------------------------------------------
    // [C++20/23] Range 자체를 넘기는 최신 방식 (concepts + ranges)
    // ------------------------------------------------------------------
    std::cout << "[C++20/23]\n";
    std::cout << "sum(int):    " << modern::my_accumulate(vec, 0) << '\n';
    std::cout << "sum(double): " << modern::my_accumulate(nums, 0.0) << '\n';
    std::cout << "join(str):   " << modern::my_accumulate(words, ""s) << '\n';

    // ------------------------------------------------------------------
    // [C++23] constexpr 덕분에 컴파일 타임에도 누적 계산이 가능 (그게 뭔데 개어렵네)
    // ------------------------------------------------------------------
    constexpr int sum_1_to_10 = modern::my_accumulate(std::views::iota(1, 11), 0);
    static_assert(sum_1_to_10 == 55, "compile-time my_accumulate failed");
    std::cout << "[C++23] constexpr 1..10 = " << sum_1_to_10 << '\n';

    return 0;
}
