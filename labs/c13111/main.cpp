#include "my_vector.h"

#include <iostream>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string>
#include <utility>

// 기본 생성도, 대입도 불가능한 타입. 인자로만 생성되고 이동만 된다.
//   - new Boxed[n] 은 기본 생성자가 없어 컴파일 실패 → raw new[] 구현을 막는다.
//   - data_[i] = Boxed(...) 는 대입 연산자가 없어 컴파일 실패 → "자리에 만들어 두고 대입"
//     방식을 막는다. 오직 std::construct_at(data_ + size_, args...) 만 통과한다.
struct Boxed {
    int v;
    explicit Boxed(int x) : v(x) {}
    Boxed() = delete;
    Boxed(const Boxed&) = default;
    Boxed(Boxed&&) = default;           // move construct를 해볼려면 내용 수정하고 log를 찍게 cout활용해서 해보기
    Boxed& operator=(const Boxed&) = delete;
    Boxed& operator=(Boxed&&) = delete;
    ~Boxed() = default;
};

// std::ranges::input_range 제약을 만족하는 임의 범위를 받아 공백으로 구분해 출력.
// my_vector 가 begin()/end() 를 제공하면 그대로 사용할 수 있다.
template <std::ranges::input_range R>
void print_values(R&& values) {
    bool first = true;
    for (const auto& value : values) {
        if (!first) {
            std::print(" ");
        }
        std::print("{}", value);
        first = false;
    }
    std::println("");
}

int main() {
    std::string mode;
    if (!(std::cin >> mode)) {
        mode = "basic";
    }

    if (mode == "basic") {
        // 초기화, size/capacity, operator[] 수정, 범위 기반 for.
        my_vector<int> v = {1, 2, 3, 4, 5};
        v[4] = 10;
        std::println("{} {}", v.size(), v.capacity());
        print_values(v);
    } else if (mode == "at_throw") {
        // at() 는 std::vector 와 동일하게 std::out_of_range 를 던진다.
        // 음수 리터럴을 size_t 로 캐스팅하면 매우 큰 양수가 되어 동일한
        // 경계 검사에 걸린다 (인덱스가 부호 없는 타입이라는 std::vector 의
        // 인터페이스를 그대로 따른다).
        my_vector<int> v = {10, 20, 30};
        try {
            std::println("ok {}", v.at(2));
            std::println("ok {}", v.at(5));
        } catch (const std::out_of_range&) {
            std::println("out_of_range: index 5");
        }
        try {
            std::println("ok {}", v.at(static_cast<std::size_t>(-1)));
        } catch (const std::out_of_range&) {
            std::println("out_of_range: index -1");
        }
    } else if (mode == "push_back") {
        // push_back 의 두 오버로드(const T& / T&&) 와 자동 capacity 성장.
        my_vector<std::string> v;
        std::string alpha = "alpha";
        v.push_back(alpha);                     // const T& 오버로드 (복사)
        v.push_back(std::string("beta"));       // T&&     오버로드 (이동)
        std::string gamma = "gamma";
        v.push_back(std::move(gamma));          // T&&     오버로드 (이동)
        std::println("{}", v.size());
        print_values(v);
    } else if (mode == "emplace_back") {
        // emplace_back : 가변 인자만 받아 빈 자리에 T 를 직접 짓는다(construct_at).
        // push_back 으로 같은 결과를 만들려면 std::string(3, 'x') 를 먼저
        // 만들어 임시 객체로 넘겨야 한다.
        my_vector<std::string> v;
        v.emplace_back("alpha");          // std::string(const char*)
        v.emplace_back(3, 'x');           // std::string(std::size_t, char)
        v.emplace_back(2, 'y');           // std::string(std::size_t, char)
        std::println("{} {}", v.size(), v.capacity() >= v.size());
        print_values(v);
    } else if (mode == "copy_move") {
        // 깊은 복사 / 복사 대입 / 자기 대입 / 이동 / 이동 대입 / 자기 이동 대입.
        my_vector<int> a = {1, 2, 3};
        my_vector<int> b(a);           // copy ctor
        b[0] = 99;
        std::println("{} {}", a[0], b[0]);            // 1 99

        my_vector<int> assigned;
        assigned = b;                  // copy assign
        assigned[1] = 88;
        std::println("{} {}", b[1], assigned[1]);     // 2 88

        assigned = assigned;           // self copy-assign (state preserved)
        std::println("{} {} {}", assigned.size(), assigned[0], assigned[2]);  // 3 99 3

        my_vector<int> c(std::move(a));               // move ctor
        std::println("{} {}", a.size(), c.size());    // 0 3

        my_vector<int> moved;
        moved = std::move(b);          // move assign
        std::println("{} {}", b.size(), moved.size());// 0 3
        moved = std::move(moved);      // self move-assign (state preserved)
        std::println("{} {}", moved.size(), moved[0]);// 3 99

        print_values(c);                              // 1 2 3
    } else if (mode == "reserve_growth") {
        // reserve 가 capacity 만 늘리고, size 는 그대로인지 확인.
        my_vector<int> v;
        v.push_back(1);
        v.reserve(8);
        v.push_back(2);
        v.push_back(3);
        std::println("{} {}", v.size(), v.capacity());
        print_values(v);
    } else if (mode == "no_default") {
        // 기본 생성도 대입도 불가능한 Boxed 를 emplace_back 으로만 채운다.
        // construct_at 기반 제자리 생성이 아니면 컴파일조차 되지 않는다.
        // 세 번째 emplace 에서 capacity 가 2 → 4 로 커지며 reserve 가 Boxed 를
        // 이동 생성으로 새 버퍼에 옮긴다(대입이 아니라 생성).
        my_vector<Boxed> v;
        v.emplace_back(1);
        v.emplace_back(2);
        v.emplace_back(3);
        std::println("{}", v.size());
        bool first = true;
        for (const Boxed& b : v) {
            if (!first) {
                std::print(" ");
            }
            std::print("{}", b.v);
            first = false;
        }
        std::println("");
    }
}
