#include <iostream>
#include <string>

#include "terminalrenderer.h"

using namespace std;

namespace {

void clearScreen(std::ostream& out) {
    static const std::string newlines(24, '\n');
    out.write(newlines.data(), newlines.size());
}

char renderCell(CellView cell) {
    switch (cell.getState()) {
    case CellView::State::Unknown:
        return ' ';
    case CellView::State::OurCortex:
        return '@';
    case CellView::State::OurTendril:
        return '+';
    default:
        return '?';
    }
}

} // anon

TerminalRenderer::TerminalRenderer():
    ostream_(std::cout)
{}

void TerminalRenderer::renderBoard(const Board<CellView>& board, Player player) {
    clearScreen(ostream_);
    ostream_ << player << "'s view:\n";

    const unsigned sideSize = board.getSideSize();

    char rendered[sideSize * (sideSize + 1)]; // row x (col + newline)
    char *out = rendered;

    for (unsigned row = 0; row < sideSize; ++row) {
        for (unsigned col = 0; col < sideSize; ++col) {
            *out++ = renderCell(board.cellAt(Position(col, row)));
        }

        *out++ = '\n';
    }

    ostream_.write(rendered, sizeof(rendered));
}

void TerminalRenderer::promptForNextPlayer(Player player) {
    clearScreen(ostream_);
    ostream_ << player << "'s turn next, pass the laptop!\n";
    ostream_ << player << " press enter to continue.\n";
    string trash;
    getline(cin, trash);
}
