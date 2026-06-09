#pragma once
#include "Skill.hpp"
#include <iostream>

// TODO: EzrealSkill 클래스를 구현하세요 (Skill을 public 상속).
// q(): "RISING SPELL FORCE" 출력
// w(): "MYSTIC SHOT" 출력
// e(): "ESSENCE FLUX" 출력
// r(): "ARCANE SHIFT" 출력
class EzrealSkill : public Skill {
    public:
        void q() override {
            std::cout<<"RISING SPELL FORCE"<<std::endl;
        }
        void w() override {
            std::cout<<"MYSTIC SHOT"<<std::endl;
        }
        void e() override {
            std::cout<<"ESSENCE FLUX"<<std::endl;
        }
        void r() override {
            std::cout<<"ARCANE SHIFT"<<std::endl;
        }
};
