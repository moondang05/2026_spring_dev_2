// 실습 115 - Solo Replay Recorder And Player
// 채점 드라이버. 첫 줄 stdin 의 모드 키워드로 시나리오를 선택한다.
// 학생은 Replay.h + Replay.cpp 만 제출하면 된다. 이 파일은 제공된다.

#include "Replay.h"
#include "replay_io.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using namespace driver_io;

namespace {

// 모드별로 분리된 임시 파일. 한 실행 안에서 모드끼리 격리.
std::string tmp_path(const std::string& tag) {
    fs::create_directories("tmp_replay115");
    return "tmp_replay115/" + tag + ".txt";
}

// 파일 한 줄을 바꾸거나 추가/삭제하기 위한 헬퍼.
std::vector<std::string> read_lines(const std::string& p) {
    std::vector<std::string> out;
    std::ifstream in(p);
    std::string line;
    while (std::getline(in, line)) out.push_back(line);
    return out;
}

void write_lines(const std::string& p, const std::vector<std::string>& lines) {
    std::ofstream out(p, std::ios::out | std::ios::trunc);
    for (const auto& l : lines) out << l << '\n';
}

void write_file(const std::string& p, const std::string& content) {
    std::ofstream out(p, std::ios::out | std::ios::trunc);
    out << content;
}

// reader 를 열어보고 결과 출력. 예외면 분류 후 보고.
void try_open_and_report(const std::string& p) {
    try {
        ReplayReader r(p);
        open_ok(r.header());
        status(r.complete(), r.checksum_ok());
    } catch (const ReplayError& e) {
        open_error(klass_name(e), e.what());
    }
}

// reader 를 열고 strict 호출까지 시도.
void try_strict_and_report(const std::string& p) {
    try {
        ReplayReader r(p);
        try {
            auto evs = r.events_strict();
            strict_count(evs.size());
            for (const auto& e : evs) event_line(e);
        } catch (const ReplayError& e) {
            strict_error(klass_name(e), e.what());
        }
    } catch (const ReplayError& e) {
        open_error(klass_name(e), e.what());
    }
}

void try_partial_and_report(const std::string& p) {
    try {
        ReplayReader r(p);
        auto evs = r.events_partial();
        partial_count(evs.size());
        for (const auto& e : evs) event_line(e);
    } catch (const ReplayError& e) {
        open_error(klass_name(e), e.what());
    }
}

// ============== 모드 핸들러 ==============

void mode_normal() {
    std::string p = tmp_path("normal");
    fs::remove(p);
    {
        ReplayHeader h{.match_id = 42, .seed = 8917, .player = "alice"};
        ReplayWriter w(p, h);
        started();
        w.append({0, "SPAWN", {{"piece", "T"}}});            appended();
        w.append({3, "LEFT",  {}});                          appended();
        w.append({5, "ROTATE_CW", {{"spin", "true"}}});      appended();
        w.finalize(100, 5);                                  finalized();
    }
    try_open_and_report(p);
    try_strict_and_report(p);
    ReplayReader r(p);
    final_summary(r.complete(), r.final_score(), r.final_tick());
}

void mode_save_quit() {
    std::string p = tmp_path("save_quit");
    fs::remove(p);
    {
        ReplayHeader h{.match_id = 1, .seed = 1, .player = "bob"};
        ReplayWriter w(p, h);
        started();
        w.append({0, "SPAWN", {{"piece", "I"}}}); appended();
        w.append({3, "RIGHT", {}});               appended();
        dropped();
        // scope 종료 시 ~ReplayWriter 가 호출되어 자동 finalize
    }
    try_open_and_report(p);
    try_partial_and_report(p);
    ReplayReader r(p);
    final_summary(r.complete(), r.final_score(), r.final_tick());
}

void mode_truncated() {
    std::string p = tmp_path("truncated");
    fs::remove(p);
    {
        ReplayHeader h{.match_id = 1, .seed = 1, .player = "c"};
        ReplayWriter w(p, h);
        started();
        w.append({0, "SPAWN", {{"piece", "O"}}}); appended();
        w.append({5, "HARD_DROP", {}});           appended();
        w.finalize(40, 5);                        finalized();
    }
    // END 줄을 외부에서 삭제 (디스크 풀 / 전송 중 끊김 시뮬)
    {
        auto lines = read_lines(p);
        if (!lines.empty() && lines.back().substr(0, 3) == "END") lines.pop_back();
        write_lines(p, lines);
    }
    corrupted("drop_end");
    try_open_and_report(p);
    try_strict_and_report(p);
    try_partial_and_report(p);
}

void mode_checksum_mismatch() {
    std::string p = tmp_path("cksum");
    fs::remove(p);
    {
        ReplayHeader h{.match_id = 1, .seed = 1, .player = "c"};
        ReplayWriter w(p, h);
        started();
        w.append({0, "SPAWN", {{"piece", "T"}}}); appended();
        w.finalize(0, 0);                         finalized();
    }
    // EVENT 줄의 첫 글자를 바꿔 checksum 깨뜨림 (S→s)
    {
        auto lines = read_lines(p);
        for (auto& l : lines) {
            if (l.rfind("EVENT ", 0) == 0) {
                auto pos = l.find("SPAWN");
                if (pos != std::string::npos) l[pos] = 's';
                break;
            }
        }
        write_lines(p, lines);
    }
    corrupted("flip_byte");
    try_open_and_report(p);
    try_strict_and_report(p);
    try_partial_and_report(p);
}

void mode_bad_magic() {
    std::string p = tmp_path("bad_magic");
    write_file(p, "WRONG_MAGIC v1\nmatch_id=1 seed=1 player=c\nEND score=0 ticks=0 checksum=0X0000\n");
    try_open_and_report(p);
}

void mode_version_errors() {
    {
        std::string p = tmp_path("v2");
        write_file(p, "TETRIS_REPLAY v2\nmatch_id=1 seed=1 player=c\nEND score=0 ticks=0 checksum=0X0000\n");
        try_open_and_report(p);
    }
    {
        std::string p = tmp_path("vX");
        write_file(p, "TETRIS_REPLAY vX\nmatch_id=1 seed=1 player=c\nEND score=0 ticks=0 checksum=0X0000\n");
        try_open_and_report(p);
    }
}

void mode_header_validation() {
    // (1) missing seed
    {
        std::string p = tmp_path("hdr_missing");
        write_file(p, "TETRIS_REPLAY v1\nmatch_id=1 player=c\n");
        try_open_and_report(p);
    }
    // (2) duplicate match_id
    {
        std::string p = tmp_path("hdr_dup");
        write_file(p, "TETRIS_REPLAY v1\nmatch_id=1 match_id=2 seed=1 player=c\n");
        try_open_and_report(p);
    }
    // (3) empty value (mode=)
    {
        std::string p = tmp_path("hdr_empty");
        write_file(p, "TETRIS_REPLAY v1\nmatch_id=1 seed=1 player=c mode=\n");
        try_open_and_report(p);
    }
    // (4) unknown key ignored
    {
        std::string p = tmp_path("hdr_unknown");
        write_file(p, "TETRIS_REPLAY v1\nseed=2 match_id=9 player=alice foo=bar tick_rate=30\n");
        try_open_and_report(p);   // expected: open_ok with v=1 match=9 seed=2 player=alice mode=marathon tick_rate=30
    }
}

void mode_write_runtime_errors() {
    // (1) tick decreased
    {
        std::string p = tmp_path("wre_tick");
        ReplayWriter w(p, ReplayHeader{.match_id = 1, .seed = 1, .player = "c"});
        w.append({5, "LEFT", {}}); appended();
        try {
            w.append({3, "RIGHT", {}});
        } catch (const ReplayError& e) {
            append_error(klass_name(e), e.what());
        }
    }
    // (2) append after finalize
    {
        std::string p = tmp_path("wre_apaf");
        ReplayWriter w(p, ReplayHeader{.match_id = 1, .seed = 1, .player = "c"});
        w.finalize(0, 0); finalized();
        try {
            w.append({0, "LEFT", {}});
        } catch (const ReplayError& e) {
            append_error(klass_name(e), e.what());
        }
    }
    // (3) double finalize
    {
        std::string p = tmp_path("wre_double");
        ReplayWriter w(p, ReplayHeader{.match_id = 1, .seed = 1, .player = "c"});
        w.finalize(0, 0); finalized();
        try {
            w.finalize(0, 0);
        } catch (const ReplayError& e) {
            finalize_error(klass_name(e), e.what());
        }
    }
    // (4) event after END (수동으로 EVENT 줄 추가)
    {
        std::string p = tmp_path("wre_eae");
        {
            ReplayWriter w(p, ReplayHeader{.match_id = 1, .seed = 1, .player = "c"});
            w.append({0, "SPAWN", {{"piece", "T"}}});
            w.finalize(0, 0);
        }
        // END 뒤에 줄 추가
        {
            std::ofstream out(p, std::ios::app);
            out << "EVENT tick=5 action=LEFT\n";
        }
        corrupted("append_after_end");
        try_strict_and_report(p);
    }
}

} // namespace

int main() {
    std::string mode;
    if (!(std::cin >> mode)) mode = "normal";

    if      (mode == "normal")                mode_normal();
    else if (mode == "save_quit")             mode_save_quit();
    else if (mode == "truncated")             mode_truncated();
    else if (mode == "checksum_mismatch")     mode_checksum_mismatch();
    else if (mode == "bad_magic")             mode_bad_magic();
    else if (mode == "version_errors")        mode_version_errors();
    else if (mode == "header_validation")     mode_header_validation();
    else if (mode == "write_runtime_errors")  mode_write_runtime_errors();
    else std::println("unknown_mode={}", mode);
    return 0;
}
