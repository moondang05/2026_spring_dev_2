// =========================================================================
// 정적 다형성 (Static Polymorphism) 테스트 드라이버
//
//   - 표준 입력 1줄: 1, 2, 3 중 하나를 읽어 챔피언을 선택합니다.
//   - fire(c) 한 줄로 세 챔피언 타입을 모두 처리합니다.
//   - 공통 부모, virtual 함수 모두 사용하지 않습니다.
//
// 이 파일은 제출 대상이 아니며 수정하지 않습니다.
// =========================================================================

#include "champions.h"
#include "fire.h"

#include <iostream>
#include <type_traits>

int main() {
    // vtable 부재 검증 — virtual 함수가 하나라도 있으면 컴파일 실패합니다.
    static_assert(!std::is_polymorphic_v<Ezreal>, "Ezreal must not be polymorphic");
    static_assert(!std::is_polymorphic_v<Garen>,  "Garen must not be polymorphic");
    static_assert(!std::is_polymorphic_v<Soraka>, "Soraka must not be polymorphic");

    int t;
    std::cin >> t;

    if      (t == 1) { Ezreal c; fire(c); }
    else if (t == 2) { Garen  c; fire(c); }
    else if (t == 3) { Soraka c; fire(c); }

    return 0;
}
