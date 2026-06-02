#include <iostream>
#include <map>
#include <string>
#include "Complex.h"

int main() {
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        // 산술 + 비교 + 특수 출력 포맷 테스트
        double r1, i1, r2, i2;
        std::cin >> r1 >> i1 >> r2 >> i2;
        Complex c1(r1, i1);
        Complex c2(r2, i2);
        Complex cs = c1 + c2;
        Complex cd = c1 - c2;

        std::cout << "c1 = " << c1 << "\n";
        std::cout << "c2 = " << c2 << "\n";
        std::cout << "c1 + c2 = " << cs << "\n";
        std::cout << "c1 - c2 = " << cd << "\n";
        std::cout << (c1 < c2 ? "c1 < c2" : "c1 >= c2") << "\n";

        // 특수 포맷: 실수만 / 허수만 / 0
        Complex cr(5, 0);
        Complex ci(0, 4);
        Complex cz(0, 0);
        std::cout << "real only: " << cr << "\n";
        std::cout << "imag only: " << ci << "\n";
        std::cout << "zero: " << cz << "\n";
    } else if (mode == 2) {
        // std::map 키 테스트 — magnitude 가 같은 서로 다른 복소수가
        // 모두 고유 키로 저장되는지 확인
        std::map<Complex, std::string> m;
        m[Complex(1, 1)] = "a";
        m[Complex(2, 0)] = "b";   // |c|=2
        m[Complex(0, 2)] = "c";   // |c|=2, 같은 크기
        m[Complex(3, 4)] = "d";
        m[Complex(1, 1)] = "a2";  // 같은 키 → 덮어쓰기

        std::cout << "map size = " << m.size() << "\n";
        for (const auto& kv : m) {
            std::cout << kv.first << " : " << kv.second << "\n";
        }
    }

    return 0;
}
