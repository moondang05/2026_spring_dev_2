#include "Range.hpp"

// ─ Iterator ─────────────────────────────────────────────
Range::Iterator::Iterator(long long current, long long step, long long stop)
    : current_(current), step_(step), stop_(stop) {}

// TODO: 현재 값 반환
long long Range::Iterator::operator*() const
{
    return current_;
}

// TODO: 전위 증가 — current_ 를 step_ 만큼 증감하고 *this 반환
Range::Iterator &Range::Iterator::operator++()
{
    current_ += step_;
    return *this;
}

// TODO: 후위 증가 — 현재 상태 사본을 만든 뒤 전위 증가, 사본 반환
Range::Iterator Range::Iterator::operator++(int)
{
    auto temp = *this; // 임시 저장하여 둠. 용량 늘어남
    ++(*this);         // 주목!! 본래의 값은 증가 함 (== curent_ += step_)
    return temp;       // 기존 값을 반환
}

// TODO: step 부호를 고려한 "끝났는지" 판단
//   - step > 0: current_ < other.current_ 이면 아직 남음 (true)
//   - step < 0: current_ > other.current_ 이면 아직 남음 (true)
//   - step == 0: 항상 끝 (false) — range 가 비어 있어야 하므로
bool Range::Iterator::operator!=(const Iterator &other) const
{
    if (step_ > 0)
        return current_ < other.current_;
    else if (step_ < 0)
        return current_ > other.current_;
    else
        return false;
}

// TODO: != 의 반대
bool Range::Iterator::operator==(const Iterator &other) const
{
    return !(*this != other); // 주목!!
}

// ─ Range ────────────────────────────────────────────────
// TODO: 3 개 생성자 — 멤버 초기화 리스트 사용
//   Range(stop)             → start=0, step=1
//   Range(start, stop)      →          step=1
//   Range(start, stop, step)
Range::Range(long long stop) : start_(0), stop_(stop), step_(1) {}
Range::Range(long long start, long long stop) : start_(start), stop_(stop), step_(1) {}
Range::Range(long long start, long long stop, long long step) : start_(start), stop_(stop), step_(step) {}

// TODO: 빈 range 조건을 검사한 뒤 Iterator 반환
//   빈 조건:
//     1) step == 0
//     2) step > 0 && start >= stop
//     3) step < 0 && start <= stop
//   빈 경우에는 begin() 을 end() 와 같게 해서 for-loop 가 0 회 돌도록 합니다.
Range::Iterator Range::begin() const
{
    if (step_ == 0 || (step_ > 0 && start_ >= stop_) || (step_ < 0 && start_ <= stop_))
        return end();
    return Iterator(start_, step_, stop_);
}

Range::Iterator Range::end() const
{
    return Iterator(stop_, step_, stop_);
}
