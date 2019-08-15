#include <iostream>
#include <string>

#include "boardloader.h"
#include "game.h"
#include "playerview.h"
#include "stdoutrenderer.h"

using namespace std;

namespace {
void usage(ostream& out, const char* argv0) {
    out << "Usage:   " << argv0 << " <map-filename>\n";
    out << "Example: " << argv0 << " maps/01.txt\n";
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

} // anon

int main(int argc, char *argv[]) {
#if 0
    if (argc < 2) {
        usage(cerr, argv[0]);
        return 1;
    }

    Board<Cell> board = loadBoard(argv[1]);

    cout << "Red view:\n";
    StdoutRenderer::renderBoard(makeBoardView(board, Player::Red), cout);

    cout << "\nBlue view:\n";
    StdoutRenderer::renderBoard(makeBoardView(board, Player::Blue), cout);

    cout << "Board size is " << board.sideSize() << "\n";
#else
    Board<Cell> board(3);
    cout << "Enter start positions (board size=" << board.getSideSize() << ").\n";
    Position blueStart = getMove(Player::Blue);
    Position redStart = getMove(Player::Red);
    // TODO: Validate start positions!
#endif

    Game g(std::move(board), blueStart, redStart, getMove);

    g.run();

    return 0;
}
