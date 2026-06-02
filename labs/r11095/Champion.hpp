#pragma once
#include "Skill.hpp"
#include "GangplankSkill.hpp"
#include "EzrealSkill.hpp"
#include <memory>

enum class CHAMPION { GANGPLANK, EZREAL };

class Champion {
public:
    void select_champion(CHAMPION champion) {
        switch (champion) {
            case CHAMPION::GANGPLANK:
                skill = std::make_unique<GangplankSkill>();
                break;
            case CHAMPION::EZREAL:
                skill = std::make_unique<EzrealSkill>();
                break;
        }
    }
    void q() { if (skill) skill->q(); }
    void w() { if (skill) skill->w(); }
    void e() { if (skill) skill->e(); }
    void r() { if (skill) skill->r(); }
private:
    std::unique_ptr<Skill> skill;
};
