#include "RenderSnapshot.hpp"

#include "tetris.h"

#include <sstream>
namespace tetris::render {

RenderSnapshot to_render_snapshot(const ::LocalSnapshot& local) {
  // LocalSnapshot은 게임 코어의 계약이고, RenderSnapshot은 렌더링용 계약입니다.
  // 이름이 같은 필드는 그대로 복사하고, next_tetromino는
  // tetromino_block(..., 0)을 이용해 4x4 미리보기 문자열로 풀어 주세요.
  RenderSnapshot render;
  render.tick = local.tick;
  render.board_rows = local.board_rows;
  render.next_piece.available = true;
  render.next_piece.tetromino = local.next_tetromino;
  render.score = local.score;
  render.level = local.level;
  render.lines_cleared = local.lines_cleared;
  render.running = local.running;

  const Block& preview = tetromino_block(local.next_tetromino, 0);
  for (int y = 0; y < RENDER_BLOCK_SIZE; ++y) {
    std::string row;
    row.reserve(RENDER_BLOCK_SIZE);
    for (int x = 0; x < RENDER_BLOCK_SIZE; ++x)
      row.push_back(preview[y][x] ? '#' : '.');
    render.next_piece.rows[y] = row;
  }
  return render;
}

std::string render_snapshot_to_text(const RenderSnapshot& snapshot) {
  // case_runner는 문자열을 정확히 비교하므로 필드 순서를 고정해야 합니다.
  // std::ostringstream를 사용해 다음 순서로 출력하세요:
  // tick/running/score/level/lines/(status가 있으면 status), next_available,
  // next, "board" + 20행, 마지막으로 "next_preview" + 4행.
  std::ostringstream out;
  out << "tick=" << snapshot.tick << "\n";
  out << "running=" << (snapshot.running ? 1 : 0) << "\n";
  out << "score=" << snapshot.score << "\n";
  out << "level=" << snapshot.level << "\n";
  out << "lines=" << snapshot.lines_cleared << "\n";
  if (!snapshot.status_text.empty())
    out << "status=" << snapshot.status_text << "\n";
  out << "next_available=" << (snapshot.next_piece.available ? 1 : 0) << "\n";
  out << "next=" << snapshot.next_piece.tetromino << "\n";
  out << "board\n";
  for (const auto& row : snapshot.board_rows) out << row << "\n";
  out << "next_preview\n";
  for (const auto& row : snapshot.next_piece.rows) out << row << "\n";
  return out.str();
}

}  // namespace tetris::render