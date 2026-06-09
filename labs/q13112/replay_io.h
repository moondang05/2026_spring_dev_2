// replay_io.h — 채점 드라이버용 출력 헬퍼.
// 학생이 읽고 이해하기 위한 *참고* 자료입니다. 학생 코드에서 호출하지 않습니다.
// 학생이 직접 출력 문자열을 타이핑할 필요가 없도록 main.cpp 가 이 헬퍼만 호출합니다.
#pragma once

#include <cstddef>
#include <format>
#include <print>
#include <string>
#include <string_view>

#include "Replay.h"

namespace driver_io {

inline void started()  { std::println("started"); }
inline void appended() { std::println("appended"); }
inline void finalized(){ std::println("finalized"); }
inline void dropped()  { std::println("dropped"); }

inline void corrupted(std::string_view mode) {
    std::println("corrupted={}", mode);
}

inline void open_ok(const ReplayHeader& h) {
    std::println("open_ok header=v={} match={} seed={} player={} mode={} tick_rate={}",
                 h.version, h.match_id, h.seed, h.player, h.mode, h.tick_rate);
}

inline void open_error(std::string_view klass, std::string_view msg) {
    std::println("open_error={}:{}", klass, msg);
}

inline void status(bool complete, bool checksum_ok) {
    std::println("status complete={} checksum_ok={}", complete ? 1 : 0, checksum_ok ? 1 : 0);
}

inline void final_summary(bool complete, int score, int tick) {
    if (complete) std::println("final score={} tick={}", score, tick);
    else           std::println("final complete=0");
}

inline void strict_count(std::size_t n) { std::println("strict_count={}", n); }
inline void partial_count(std::size_t n){ std::println("partial_count={}", n); }

inline void event_line(const ReplayEvent& ev) {
    std::string s = std::format("event tick={} action={}", ev.tick, ev.action);
    for (const auto& kv : ev.extras) {
        s += ' '; s += kv.first; s += '='; s += kv.second;
    }
    std::println("{}", s);
}

inline void append_error(std::string_view klass, std::string_view msg) {
    std::println("append_error={}:{}", klass, msg);
}
inline void finalize_error(std::string_view klass, std::string_view msg) {
    std::println("finalize_error={}:{}", klass, msg);
}
inline void strict_error(std::string_view klass, std::string_view msg) {
    std::println("strict_error={}:{}", klass, msg);
}

inline const char* klass_name(const ReplayError& e) noexcept {
    if (dynamic_cast<const ReplayIoError*>(&e))      return "ReplayIoError";
    if (dynamic_cast<const ReplayVersionError*>(&e)) return "ReplayVersionError";
    if (dynamic_cast<const ReplayFormatError*>(&e))  return "ReplayFormatError";
    return "ReplayError";
}

} // namespace driver_io
