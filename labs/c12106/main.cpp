// =========================================================================
// Deducing This mixin 테스트 드라이버
//
//   - 표준 입력 1줄: 1, 2, 3 중 하나를 읽어 챔피언 시나리오를 선택합니다.
//   - 마나 기반 챔피언(Ezreal, Lux) 은 try_cast 를, 쿨다운 기반 챔피언
//     (Garen) 은 try_skill / tick 을 호출합니다. 두 동작은 서로 다른 mixin
//     (Castable, CooldownTracked) 에서 *한 자리에 한 번만* 정의됩니다.
//
// 이 파일은 제출 대상이 아니며 수정하지 않습니다.
// =========================================================================

#include "castable.h"

#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

// --- 컴파일 타임 구조 검증 ---------------------------------------------------

// (1) vtable 부재 — virtual 함수가 있으면 컴파일 실패합니다.
static_assert(!std::is_polymorphic_v<Ezreal>, "Ezreal must not be polymorphic");
static_assert(!std::is_polymorphic_v<Lux>,    "Lux must not be polymorphic");
static_assert(!std::is_polymorphic_v<Garen>,  "Garen must not be polymorphic");

// (2) 두 mixin 은 *데이터 멤버를 갖지 않습니다*. 상태는 자식이 소유합니다.
static_assert(std::is_empty_v<Castable>,         "Castable mixin must have no data members");
static_assert(std::is_empty_v<CooldownTracked>,  "CooldownTracked mixin must have no data members");

// (3) 상속 관계 — 마나 기반 챔피언은 Castable 을, 쿨다운 챔피언은
//     CooldownTracked 만 상속합니다. Garen 이 Castable 도 함께 상속하면
//     "마나 없는 챔피언에 마나 로직이 주입된" 잘못된 구조이므로 차단됩니다.
static_assert( std::is_base_of_v<Castable,        Ezreal>, "Ezreal must inherit Castable");
static_assert( std::is_base_of_v<Castable,        Lux>,    "Lux must inherit Castable");
static_assert( std::is_base_of_v<CooldownTracked, Garen>,  "Garen must inherit CooldownTracked");
static_assert(!std::is_base_of_v<Castable,        Garen>,  "Garen must NOT inherit Castable");

// (4) 기능은 mixin 본체에 있어야 합니다 — 자식이 아니라.  최소 재료만 가진
//     probe 타입이 mixin 함수에 그대로 닿는지 확인합니다.  학생이 try_cast /
//     try_skill / tick 을 자식 클래스 안에서만 구현하면 이 probe 는 닿지
//     못해 컴파일 타임에 막힙니다.
namespace mixin_probe_ {
    struct ManaProbe : Castable {
        int mana = 1;
        int cost() const { return 1; }
        std::string name() const { return "P"; }
    };
    struct CooldownProbe : CooldownTracked {
        int cooldown = 0;
        int max_cooldown() const { return 1; }
        std::string name() const { return "P"; }
    };
    template <class T> concept HasTryCast =
        requires(T t) { t.try_cast(std::string_view{"x"}); };
    template <class T> concept HasTrySkillAndTick =
        requires(T t) { t.try_skill(std::string_view{"x"}); t.tick(); };
    static_assert(HasTryCast<ManaProbe>,
        "Castable must provide try_cast(this Self&, std::string_view) to its subclass");
    static_assert(HasTrySkillAndTick<CooldownProbe>,
        "CooldownTracked must provide try_skill / tick to its subclass");
}

// --- 시나리오 실행 -----------------------------------------------------------

int main() {
    int t;
    std::cin >> t;

    if (t == 1) {
        Ezreal e;
        e.try_cast("Tower");
        e.try_cast("Tower");
        e.try_cast("Tower");
    } else if (t == 2) {
        Lux l;
        l.try_cast("Minion");
        l.try_cast("Minion");
    } else if (t == 3) {
        Garen g;
        g.try_skill("Baron");   // ready  → uses, cooldown=2
        g.try_skill("Baron");   // cd=2   → on cooldown
        g.tick();               // cd=2 → 1
        g.tick();               // cd=1 → 0
        g.tick();               // cd=0 → 0   (※ -1 로 떨어지면 잘못된 구현)
        g.try_skill("Baron");   // ready  → uses, cooldown=2  (잘못된 구현은 "on cooldown (-1)" 출력)
    }

    return 0;
}
