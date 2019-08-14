#include <iostream>
#include <string>

#include "boardloader.h"
#include "playerview.h"
#include "stdoutrenderer.h"

using namespace std;

namespace {
void usage(ostream& out, const char* argv0) {
    out << "Usage:   " << argv0 << " <map-filename>\n";
    out << "Example: " << argv0 << " maps/01.txt\n";
}
} // anon

int main(int argc, char *argv[]) {

    if (argc < 2) {
        usage(cerr, argv[0]);
        return 1;
    }

    Board<Cell> board = loadBoard(argv[1]);

    cout << "Red view:\n";
    StdoutRenderer::renderBoard(makeBoardView(board, Player::Red), cout);

    cout << "\nBlue view:\n";
    StdoutRenderer::renderBoard(makeBoardView(board, Player::Blue), cout);

    return 0;
}
