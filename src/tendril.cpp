#include <iostream>
#include <string>

#include "boardloader.h"
#include "game.h"
#include "playerview.h"
#include "terminalrenderer.h"

using namespace std;

namespace {

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

} // anon

int main(int argc, char *argv[]) {
    TerminalRenderer terminalRenderer;

    Board<Cell> board(3);
    cout << "Enter start positions (board size=" << board.getSideSize() << ").\n";
    Position blueStart = getMove(Player::Blue);
    Position redStart = getMove(Player::Red);
    // TODO: Validate start positions!

    Game g(&terminalRenderer, std::move(board), blueStart, redStart, getMove);

    g.run();

    return 0;
}
