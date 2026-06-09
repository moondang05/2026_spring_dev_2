// [제공 파일 — 수정 금지]
//
// 채점기는 첫 줄로 시나리오 이름을 입력 받아 5 가지 케이스 중 하나를 실행한다.
//   * scores   — 학생 점수표. 두 과목의 평균을 0-based half-open 으로 계산.
//   * subjects — 다른 학생 점수표. 평균 계산 결과 검증.
//   * prices   — 가격표. 단일 열의 평균 (소수만 들어있는 경우).
//   * ragged   — 행마다 열 개수가 다른 초기값으로 Excel 을 만들면 생성자가
//                std::invalid_argument 를 던지는지 검증.
//   * oob      — 시트 밖 범위를 average 에 넘기면 std::out_of_range 를 던지는지
//                검증.
//
// 좌표는 모두 STL 의 [first, last) half-open. 예) 헤더 행을 제외한 학생 데이터
// 만 평균에 넣으려면 average(1, col, 4, col + 1) 처럼 행 범위를 [1, 4) 로,
// 열 범위를 폭 1 로 지정한다.

#include "Excel.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

void test_scores() {
    Excel excel{
        {Cell("Name"), Cell("C++"), Cell("Java")},
        {Cell("Kim"),  Cell(87),    Cell(75.7)  },
        {Cell("Lee"),  Cell(90),    Cell(80.6)  },
        {Cell("Park"), Cell(70),    Cell(90.0)  },
    };
    std::cout << excel.display();

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "C++ Avg. Score: "  << excel.average(1, 1, 4, 2) << '\n';
    std::cout << "Java Avg. Score: " << excel.average(1, 2, 4, 3) << '\n';
}

void test_subjects() {
    Excel excel{
        {Cell("Student"), Cell("Math"), Cell("Physics")},
        {Cell("Alice"),   Cell(92),     Cell(88.5)     },
        {Cell("Bob"),     Cell(78),     Cell(90.0)     },
        {Cell("Charlie"), Cell(85),     Cell(85.5)     },
    };
    std::cout << excel.display();

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Math Avg. Score: "    << excel.average(1, 1, 4, 2) << '\n';
    std::cout << "Physics Avg. Score: " << excel.average(1, 2, 4, 3) << '\n';
}

void test_prices() {
    Excel excel{
        {Cell("Item"),     Cell("Price")},
        {Cell("Pen"),      Cell(1.5)    },
        {Cell("Notebook"), Cell(2.8)    },
        {Cell("Eraser"),   Cell(0.8)    },
    };
    std::cout << excel.display();

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Average Price: " << excel.average(1, 1, 4, 2) << '\n';
}

void test_ragged() {
    try {
        Excel bad{
            {Cell("a"), Cell("b"), Cell("c")},
            {Cell("d"), Cell("e")           },
        };
        std::cout << "no exception\n";
    } catch (const std::invalid_argument&) {
        std::cout << "invalid_argument\n";
    }
}

void test_oob() {
    Excel excel{
        {Cell(1), Cell(2)},
        {Cell(3), Cell(4)},
    };
    try {
        // 시트는 2x2 인데 (0,0)~(5,5) 를 요구 — half-open 이라도 끝 인덱스가
        // 차원을 넘어가므로 check_range 가 즉시 던져야 한다.
        (void)excel.average(0, 0, 5, 5);
        std::cout << "no exception\n";
    } catch (const std::out_of_range&) {
        std::cout << "out_of_range\n";
    }
}

int main() {
    std::string mode;
    if (!(std::cin >> mode)) {
        mode = "scores";
    }

    if (mode == "scores") {
        test_scores();
    } else if (mode == "subjects") {
        test_subjects();
    } else if (mode == "prices") {
        test_prices();
    } else if (mode == "ragged") {
        test_ragged();
    } else if (mode == "oob") {
        test_oob();
    }
}
