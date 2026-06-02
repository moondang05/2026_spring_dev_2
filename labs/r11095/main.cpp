#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include "Champion.hpp"

using namespace std;

CHAMPION getChampion() {
    map<string, CHAMPION> cmds = {
        {"gangplank", CHAMPION::GANGPLANK},
        {"ezreal",    CHAMPION::EZREAL}
    };
    string champion;
    cin >> champion;
    auto it = cmds.find(champion);
    if (it == cmds.end()) {
        std::cerr << "Unknown champion: " << champion << "\n";
        return CHAMPION::GANGPLANK;
    }
    return it->second;
}

enum class COMMAND { SELECT, QUIT };
COMMAND getCommand() {
    string cmd;
    cin >> cmd;
    if (cmd == "select") return COMMAND::SELECT;
    return COMMAND::QUIT;
}

int main() {
    COMMAND cmd;
    while ((cmd = getCommand()) != COMMAND::QUIT) {
        switch (cmd) {
            case COMMAND::SELECT: {
                Champion c;
                c.select_champion(getChampion());
                c.q(); c.w(); c.e(); c.r();
                break;
            }
        }
    }
    return 0;
}
