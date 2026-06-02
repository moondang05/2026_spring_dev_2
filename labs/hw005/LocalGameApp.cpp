#include "LocalGameApp.hpp"

#include <chrono>
#include <thread>

LocalGameApp::LocalGameApp(GameCore core, IRenderer& renderer, IInput& input,
                           int tick_rate_hz)
    : core_(std::move(core)),
      renderer_(renderer),
      input_(input),
      tick_rate_hz_(tick_rate_hz) {}

void LocalGameApp::singleTick() {
  // 테스트 용도: pollAction 전에 먼저 — RecordingInput이 어느 tick인지 기록할
  // 수 있도록
  input_.advanceTick(tick_count_);
  // 한 tick의 순서는 고정입니다:
  // pollAction -> applyInput -> core_.step() -> render(snapshot) ->
  // ++tick_count_. advanceTick()이 pollAction()보다 먼저 와야 RecordingInput과
  // ReplayInput이 같은 tick 번호에 액션을 정확히 붙일 수 있습니다.
  if (auto action = input_.pollAction()) {
    core_.applyInput(*action);
  }
  core_.step();
  renderer_.render(tetris::render::to_render_snapshot(core_.snapshot()));
  ++tick_count_;
}

void LocalGameApp::run(int max_ticks) {
  // max_ticks번 실행할 때까지 반복합니다. max_ticks < 0이면 제한 없이
  // 반복합니다. core_.snapshot().running이 false가 되면 즉시 멈춥니다. 실제
  // 앱에서는 한 프레임 목표 시간(1000 / tick_rate_hz_ ms)에서 singleTick()에
  // 이미 쓴 시간을 뺀 만큼만 sleep하면 됩니다.
  const auto frame = std::chrono::milliseconds(1000 / tick_rate_hz_);
  int count = 0;
  while (max_ticks < 0 || count < max_ticks) {
    const auto start = std::chrono::steady_clock::now();
    singleTick();
    ++count;
    if (!core_.snapshot().running) break;
    const auto elapsed = std::chrono::steady_clock::now() - start;
    if (elapsed < frame) {
      std::this_thread::sleep_for(frame - elapsed);
    }
  }
}