#include "my_make_unique.hpp"
#include "my_unique_ptr.hpp"

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

struct Counter {
    inline static int constructed = 0;
    inline static int destroyed = 0;

    int value;

    explicit Counter(int value) : value(value) {
        ++constructed;
    }

    ~Counter() {
        ++destroyed;
    }
};

struct Widget {
    inline static int copies = 0;
    inline static int moves = 0;

    std::string label;

    explicit Widget(const std::string& text) : label(text) {
        ++copies;
    }

    explicit Widget(std::string&& text) : label(std::move(text)) {
        ++moves;
    }
};

static_assert(!std::is_copy_constructible_v<my_unique_ptr<int>>);
static_assert(!std::is_copy_assignable_v<my_unique_ptr<int>>);
static_assert(std::is_move_constructible_v<my_unique_ptr<int>>);
static_assert(std::is_move_assignable_v<my_unique_ptr<int>>);

void run_basic() {
    Counter::constructed = 0;
    Counter::destroyed = 0;

    {
        my_unique_ptr<Counter> ptr(new Counter(42));
        std::cout << ptr->value << '\n';
    }

    std::cout << Counter::constructed << ' ' << Counter::destroyed << '\n';
    if (Counter::destroyed != Counter::constructed) {
        std::cout << "destructor mismatch\n";
    }
}

void run_move() {
    my_unique_ptr<int> first(new int(15));
    my_unique_ptr<int> second(std::move(first));

    std::cout << static_cast<bool>(first) << ' '
              << static_cast<bool>(second) << ' '
              << *second << '\n';

    my_unique_ptr<int> third;
    third = std::move(second);
    if (!second && third && *third == 15) {
        std::cout << "move-only\n";
    }
}

void run_forward() {
    std::string alpha = "alpha";
    Widget::copies = 0;
    Widget::moves = 0;
    auto copied = my_make_unique<Widget>(alpha);
    std::cout << "copy:" << Widget::copies
              << " move:" << Widget::moves
              << " label:" << copied->label << '\n';

    Widget::copies = 0;
    Widget::moves = 0;
    auto moved = my_make_unique<Widget>(std::string("beta"));
    std::cout << "copy:" << Widget::copies
              << " move:" << Widget::moves
              << " label:" << moved->label << '\n';
}

int main() {
    std::string mode;
    if (!(std::cin >> mode)) {
        mode = "basic";
    }

    if (mode == "basic") {
        run_basic();
    } else if (mode == "move") {
        run_move();
    } else if (mode == "forward") {
        run_forward();
    }
}
