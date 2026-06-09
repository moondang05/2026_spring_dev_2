#ifndef TETRIS_ASSIGNMENT_005_IINPUT_HPP
#define TETRIS_ASSIGNMENT_005_IINPUT_HPP

#include "GameAction.hpp"

#include <optional>

class IInput {
public:
    virtual ~IInput() = default;
    // 매 tick마다 pollAction() 전에 호출된다. 기본 구현은 no-op이지만,
    // ScriptInput/RecordingInput처럼 tick-aware 어댑터는 이 호출로 현재 tick을 갱신해
    // 예약 액션이나 입력 기록의 tick 번호를 맞춘다.
    virtual void advanceTick(int) {}
    virtual std::optional<GameAction> pollAction() = 0;
};

#endif
