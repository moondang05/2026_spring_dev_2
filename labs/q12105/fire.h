#pragma once

// =========================================================================
// fire.h — 정적 다형성으로 챔피언의 스킬을 발사하는 함수 템플릿
//
//   - 호출되는 함수가 *컴파일 타임에* 타입으로 결정되므로 vtable 이 없습니다.
//   - 세 챔피언(Ezreal, Garen, Soraka) 은 공통 부모가 없고, virtual 함수도
//     사용하지 않습니다. 같은 이름 cast() 만 가지면 통과합니다 (덕 타이핑).
//   - Soraka 만 추가로 heal() 멤버를 가집니다. 이 분기는 if constexpr +
//     requires 로 *컴파일 가능한 타입에서만* 활성화되어야 합니다.
//
//   필수 사용: template, if constexpr, requires
//   사용 금지: virtual, printf, scanf, malloc, free
// =========================================================================

// TODO: 함수 템플릿 fire(const Champ& c) 를 작성하세요.
//   1) c.cast() 를 호출합니다.
//   2) c.heal() 이 *컴파일 가능한 경우에만* c.heal() 도 호출합니다.
//      (힌트) if constexpr (requires { c.heal(); }) { ... }
template <class Champ>
void fire(const Champ& c) {
    c.cast();
    if constexpr (requires { c.heal(); }) {
        c.heal();
    }
}