#pragma once

// =========================================================================
// castable.h — Deducing This 로 만드는 mixin
//
//   - 두 개의 mixin 과 세 챔피언을 *이 파일 한 곳에* 정의합니다.
//   - 두 mixin 은 *데이터 멤버를 갖지 않는* 빈 struct 입니다. 스킬 시전에
//     필요한 상태(mana, cooldown, name 등) 는 자식이 소유합니다.
//   - 멤버 함수 템플릿의 첫 매개변수에 `this Self& self` (C++23 deducing
//     this) 를 적으면, 호출 시 *자식 타입* 이 Self 로 추론되어 자식의
//     멤버에 직접 접근할 수 있습니다.
//
//   필수 사용: template, this Self
//   사용 금지: virtual, printf, scanf, malloc, free
// =========================================================================

#include <iostream>
#include <string>
#include <string_view>

// TODO 1: struct Castable
//   - 멤버 함수 템플릿 try_cast(this Self& self, std::string_view target)
//   - self.mana >= self.cost() 이면 mana 를 cost() 만큼 차감하고
//       "{name} casts on {target} (mana left: {mana})\n" 을 출력합니다.
//     아니면 mana 를 건드리지 않고 "{name} out of mana\n" 을 출력합니다.
struct Castable
{
    template <typename Self>
    void try_cast(this Self &self, std::string_view target)
    {
        if (self.mana >= self.cost())
        {
            self.mana -= self.cost();
            std::cout << self.name() << " casts on " << target
                      << " (mana left: " << self.mana << ")\n";
        }
        else
        {
            std::cout << self.name() << " out of mana\n";
        }
    }
};

// TODO 2: struct CooldownTracked
//   - 멤버 함수 템플릿 try_skill(this Self& self, std::string_view target)
//   - self.cooldown == 0 이면 cooldown 을 max_cooldown() 으로 채우고
//       "{name} uses skill on {target} (cooldown set to: {cooldown})\n" 을 출력합니다.
//     아니면 cooldown 을 건드리지 않고 "{name} skill on cooldown ({cooldown})\n" 을 출력합니다.
//   - 멤버 함수 템플릿 tick(this Self& self)
//   - cooldown > 0 이면 1 만큼 감소시킵니다 (0 미만으로 떨어지지 않음).
struct CooldownTracked
{
    template <typename Self>
    void try_skill(this Self &self, std::string_view target)
    {
        if (self.cooldown == 0)
        {
            self.cooldown = self.max_cooldown();
            std::cout << self.name() << " uses skill on " << target
                      << " (cooldown set to: " << self.cooldown << ")\n";
        }
        else
        {
            std::cout << self.name() << " skill on cooldown (" << self.cooldown << ")\n";
        }
    }

    template <typename Self>
    void tick(this Self &self)
    {
        if (self.cooldown > 0)
        {
            --self.cooldown;
        }
    }
};

// TODO 3: 세 챔피언 정의
//   - struct Ezreal : Castable        — mana=100, cost()=30, name()="Ezreal"
//   - struct Lux    : Castable        — mana=80,  cost()=50, name()="Lux"
//   - struct Garen  : CooldownTracked — cooldown=0, max_cooldown()=2,
//                                       name()="Garen"
//     (Garen 은 마나가 없으므로 Castable 을 상속하지 않습니다.)
struct Ezreal : Castable
{
    int mana = 100;
    int cost() const { return 30; }
    std::string name() const { return "Ezreal"; }
};

struct Lux : Castable
{
    int mana = 80;
    int cost() const { return 50; }
    std::string name() const { return "Lux"; }
};

struct Garen : CooldownTracked
{
    int cooldown = 0;
    int max_cooldown() const { return 2; }
    std::string name() const { return "Garen"; }
};