#include "Replay.h"

// TODO: 다음 함수들을 정의하세요. 인터페이스/규칙/힌트 참조.
//
ReplayWriter::ReplayWriter(std::string path, ReplayHeader header) : path_(path), header_(header) {
  out_.open(path);
  if (out_.is_open()) {
    out_ << header_.version << " "
    << header_.match_id << " "
    << header_.seed << " "
    << header_.player << " "
    << header_.mode << " "
    << header_.tick_rate << "\n";
  }
}

ReplayWriter::~ReplayWriter() {}
ReplayWriter::append(const ReplayEvent &ev) {
  last_tick_ = ev.tick;
  if (out_.is_open()) {
    out_ << last_tick_ << " " <<ev.action;
  }
  for (const auto& pair : ev.extras) {
    out_ << " " << pair.first << pair.second;
  }
  out_ << "\n";
}
ReplayWriter::finalize(int final_score, int final_tick) {}
ReplayWriter::finalized() const noexcept {}

ReplayReader::ReplayReader(std::string path) {}
ReplayReader::header() const noexcept {}
ReplayReader::complete() const noexcept {}
ReplayReader::checksum_ok() const noexcept {}
ReplayReader::final_score() const noexcept {}
ReplayReader::final_tick() const noexcept {}
ReplayReader::events_strict() const {}
ReplayReader::events_partial() const {}

//
// 출력 헬퍼 (replay_io.h) 는 채점 드라이버 main.cpp 가 호출합니다.
// 학생 코드에서 std::print / std::cout 등을 직접 호출할 필요가 없습니다.
