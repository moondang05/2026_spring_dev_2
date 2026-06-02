#pragma once

// =========================================================================
// champions.h (제공) — 세 챔피언 타입.
//
//   - 셋 다 서로를 모릅니다. 공통 부모 클래스도 없습니다.
//   - virtual 함수가 없으므로 vtable 이 생성되지 않습니다.
//   - 같은 이름 cast() 를 가지면 fire() 에서 일관되게 호출됩니다 (덕 타이핑).
//   - Soraka 만 추가로 heal() 멤버를 가집니다.
//
// 이 파일은 제출 대상이 아니며 수정하지 않습니다.
// =========================================================================

#include <iostream>

struct Ezreal {
    void cast() const { std::cout << "Ezreal: Mystic Shot 80 damage\n"; }
};

struct Garen {
    void cast() const { std::cout << "Garen: Decisive Strike 120 damage\n"; }
};

struct Soraka {
    void cast() const { std::cout << "Soraka: Starcall 60 damage\n"; }
    void heal() const { std::cout << "    Soraka: Astral Infusion +30 heal\n"; }
};
