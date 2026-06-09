#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct ReplayHeader
{
    int version{1};
    int match_id{0};
    int seed{0};
    std::string player;
    std::string mode{"marathon"};
    int tick_rate{20};
};

struct ReplayEvent
{
    int tick{0};
    std::string action;
    std::vector<std::pair<std::string, std::string>> extras;
};

// 예외 계층 (4 종) — 학생 정의 영역
class ReplayError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class ReplayIoError : public ReplayError
{
public:
    using ReplayError::ReplayError;
};

class ReplayFormatError : public ReplayError
{
public:
    using ReplayError::ReplayError;
};

class ReplayVersionError : public ReplayError
{
public:
    using ReplayError::ReplayError;
};

class ReplayWriter
{
public:
    ReplayWriter(std::string path, ReplayHeader header);
    ~ReplayWriter();

    void append(const ReplayEvent &ev);
    void finalize(int final_score, int final_tick);
    bool finalized() const noexcept;

    // copy/move 금지 — RAII 핵심에 집중하도록.
    ReplayWriter(const ReplayWriter &) = delete;
    ReplayWriter &operator=(const ReplayWriter &) = delete;
    ReplayWriter(ReplayWriter &&) = delete;
    ReplayWriter &operator=(ReplayWriter &&) = delete;

private:
    // TODO: path_, out_ (std::ofstream), header_, last_tick_, finalized_,
    //       running_sum_(unsigned) 같은 멤버를 두면 좋다.
    std::string path_=header_.mode;
    std::ofstream out_;
    ReplayHeader header_;
    int last_tick_=header_.tick_rate;
    bool finalized_=false;
    unsigned int running_sum_=0;
};

class ReplayReader
{
public:
    explicit ReplayReader(std::string path);

    const ReplayHeader &header() const noexcept;
    bool complete() const noexcept;
    bool checksum_ok() const noexcept;
    int final_score() const noexcept;
    int final_tick() const noexcept;

    std::vector<ReplayEvent> events_strict() const;
    std::vector<ReplayEvent> events_partial() const;

private:
    // TODO: header_, events_, complete_, checksum_ok_, final_score_, final_tick_,
    //       end_followed_by_garbage_ 같은 멤버를 두면 좋다.
    std::string header_;
    std::string events_;
};
