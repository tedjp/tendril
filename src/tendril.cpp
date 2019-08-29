#include <iostream>
#include <string>
#include <utility>

#include "boardloader.h"
#include "engine.h"
#include "game.h"
#include "playerview.h"
#include "textui.h"

using namespace std;

int main(int argc, char *argv[]) {
    TextUI textUI;

    static const unsigned DEFAULT_BOARD_SIZE = 4;

    unsigned boardSize = DEFAULT_BOARD_SIZE;
    if (argc > 1)
        boardSize = stoul(argv[1]);

    if (boardSize < 2) {
        cerr << "Board size must be at least 2\n";
        return 1;
    }

    Board<Cell> board(boardSize);

    pair<Position, Position> startPositions = getStartPositions(board.getSideSize());

    Game game(std::move(board), startPositions.first, startPositions.second);

    Engine().run(game, textUI);

    return 0;
}
