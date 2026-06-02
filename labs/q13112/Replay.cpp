#include "Replay.h"

// TODO: 다음 함수들을 정의하세요. 0001.html 의 인터페이스/규칙/힌트 참조.
//
//   ReplayWriter::ReplayWriter(std::string path, ReplayHeader header)
//   ReplayWriter::~ReplayWriter()
//   ReplayWriter::append(const ReplayEvent& ev)
//   ReplayWriter::finalize(int final_score, int final_tick)
//   ReplayWriter::finalized() const noexcept
//
//   ReplayReader::ReplayReader(std::string path)
//   ReplayReader::header() const noexcept
//   ReplayReader::complete() const noexcept
//   ReplayReader::checksum_ok() const noexcept
//   ReplayReader::final_score() const noexcept
//   ReplayReader::final_tick() const noexcept
//   ReplayReader::events_strict() const
//   ReplayReader::events_partial() const
//
// 출력 헬퍼 (replay_io.h) 는 채점 드라이버 main.cpp 가 호출합니다.
// 학생 코드에서 std::print / std::cout 등을 직접 호출할 필요가 없습니다.
