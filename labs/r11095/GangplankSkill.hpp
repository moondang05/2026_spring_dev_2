#pragma once
#include "Skill.hpp"
#include <iostream>

// TODO: GangplankSkill 클래스를 구현하세요 (Skill을 public 상속).
// q(): "TRIAL BY FIRE" 출력
// w(): "PARRRLEY" 출력
// e(): "REMOVE SCURVY" 출력
// r(): "POWDER KEG" 출력
class GangplankSkill : public Skill {
    public:
        void q() override {
            std::cout<<"TRIAL BY FIRE"<<std::endl;
        }
        void w() override {
            std::cout<<"PARRRLEY"<<std::endl;
        }
        void e() override {
            std::cout<<"REMOVE SCURVY"<<std::endl;
        }
        void r() override {
            std::cout<<"POWDER KEG"<<std::endl;
        }
};
