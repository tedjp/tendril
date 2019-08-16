#include <iostream>
#include <random>
#include <string>
#include <utility>

#include "boardloader.h"
#include "game.h"
#include "playerview.h"
#include "terminalrenderer.h"

using namespace std;

namespace {

Position randomPosition(unsigned boardSize) {
    random_device rd;
    uniform_int_distribution<unsigned> distribution(0, boardSize - 1);
    return Position(distribution(rd), distribution(rd));
}

Position getMove(Player player) {
    // TODO: ANSI color codes on the prompt
    cout << player << "'s move? ";

    char col, row;

    cin >> col >> row;

    // Throw away newline. maybe unnecessary
    string trash;
    getline(cin, trash);

    return positionFromAlpha(col, row);
}

pair<Position, Position> getStartPositions(unsigned boardSize) {
    Position first = randomPosition(boardSize);
    Position second = first;
    while (second == first)
        second = randomPosition(boardSize);

    return {first, second};
}

} // anon

int main(int argc, char *argv[]) {
    TerminalRenderer terminalRenderer;

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

    Game g(&terminalRenderer, std::move(board), startPositions.first, startPositions.second, getMove);

    g.run();

    return 0;
}
