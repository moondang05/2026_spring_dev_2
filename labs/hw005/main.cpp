#include "LocalGameApp.hpp"
#include "RenderSnapshot.hpp"

#include <cstdint>
#include <iostream>
#include <istream>
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace {

using tetris::render::RENDER_BOARD_HEIGHT;
using tetris::render::RenderSnapshot;
using tetris::render::render_snapshot_to_text;
using tetris::render::to_render_snapshot;

class CaptureRenderer final : public IRenderer {
public:
    void render(const RenderSnapshot& snapshot) override {
        last = snapshot;
        ++count;
    }
    RenderSnapshot last;
    int count = 0;
};

class ScriptInput final : public IInput {
public:
    void advanceTick(int tick) override {
        current_tick_ = tick;
    }
    std::optional<GameAction> pollAction() override {
        for (auto it = scheduled_.begin(); it != scheduled_.end(); ++it) {
            if (it->first == current_tick_) {
                GameAction action = it->second;
                scheduled_.erase(it);
                return action;
            }
        }
        if (actions_.empty()) {
            return std::nullopt;
        }
        GameAction action = actions_.front();
        actions_.pop();
        return action;
    }
    void pushAction(GameAction action) { actions_.push(action); }
    void scheduleAt(int tick, GameAction action) { scheduled_.emplace_back(tick, action); }

private:
    std::queue<GameAction> actions_;
    std::vector<std::pair<int, GameAction>> scheduled_;
    int current_tick_ = 0;
};

void fill_rows(std::array<std::string, RENDER_BOARD_HEIGHT>& rows, const std::string& value = "..........") {
    rows.fill(value);
}

LocalSnapshot make_local_snapshot(int tick, int next, int score, int level, int lines, int running,
                                  const std::string& row0,
                                  const std::string& row19) {
    LocalSnapshot local;
    local.tick = static_cast<std::uint32_t>(tick);
    fill_rows(local.board_rows);
    local.board_rows[0] = row0;
    local.board_rows[19] = row19;
    local.next_tetromino = next;
    local.score = score;
    local.level = level;
    local.lines_cleared = lines;
    local.running = (running != 0);
    return local;
}

} // namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::istream& input = std::cin;

    std::uint32_t seed = 888;
    std::unique_ptr<ScriptInput> script;
    std::unique_ptr<CaptureRenderer> renderer;
    std::unique_ptr<LocalGameApp> app;
    auto ensure = [&]() {
        if (!app) {
            script = std::make_unique<ScriptInput>();
            renderer = std::make_unique<CaptureRenderer>();
            app = std::make_unique<LocalGameApp>(GameCore(seed), *renderer, *script, 2000);
        }
    };

    std::string token;
    while (input >> token) {
        if (token == "seed") {
            input >> seed;
            app.reset();
            renderer.reset();
            script.reset();
        } else if (token == "init") {
            app.reset();
            renderer.reset();
            script.reset();
            ensure();
        } else if (token == "act") {
            ensure();
            std::string action_token;
            input >> action_token;
            script->pushAction(parse_action(action_token));
        } else if (token == "at") {
            ensure();
            int tick = 0;
            std::string action_token;
            input >> tick >> action_token;
            script->scheduleAt(tick, parse_action(action_token));
        } else if (token == "tick") {
            ensure();
            int n = 0;
            input >> n;
            for (int i = 0; i < n; ++i) {
                app->singleTick();
            }
        } else if (token == "run") {
            ensure();
            int n = 0;
            input >> n;
            app->run(n);
        } else if (token == "snap") {
            ensure();
            std::cout << render_snapshot_to_text(renderer->last);
        } else if (token == "count") {
            ensure();
            std::cout << "renders=" << renderer->count << '\n';
        } else if (token == "to_render") {
            int t = 0, n = 0, s = 0, l = 0, ln = 0, r = 0;
            std::string row0, row19;
            input >> t >> n >> s >> l >> ln >> r >> row0 >> row19;
            const LocalSnapshot local = make_local_snapshot(t, n, s, l, ln, r, row0, row19);
            std::cout << render_snapshot_to_text(to_render_snapshot(local));
        } else if (token == "manual") {
            int t = 0, n = 0, s = 0, l = 0, ln = 0, r = 0, avail = 0;
            std::string status;
            input >> t >> n >> s >> l >> ln >> r >> avail >> status;
            RenderSnapshot snap;
            snap.tick = static_cast<std::uint32_t>(t);
            fill_rows(snap.board_rows);
            snap.board_rows[0] = "#.........";
            snap.board_rows[19] = ".........#";
            snap.next_piece.available = (avail != 0);
            snap.next_piece.tetromino = n;
            snap.next_piece.rows = {"....", "####", "....", "...."};
            snap.score = s;
            snap.level = l;
            snap.lines_cleared = ln;
            snap.running = (r != 0);
            snap.status_text = (status == "_") ? std::string{} : status;
            std::cout << render_snapshot_to_text(snap);
        } else if (token == "parse") {
            std::string action_token;
            input >> action_token;
            std::cout << "parse(" << action_token << ")=" << action_to_string(parse_action(action_token)) << '\n';
        } else if (token == "end") {
            break;
        } else {
            std::cerr << "unknown command: " << token << '\n';
            return 2;
        }
    }
    return 0;
}
