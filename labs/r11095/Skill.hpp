#pragma once

class Skill {
public:
    virtual void q() = 0;
    virtual void w() = 0;
    virtual void e() = 0;
    virtual void r() = 0;
    virtual ~Skill() = default;
};
