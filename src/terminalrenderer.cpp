#include <iostream>

#include "terminalrenderer.h"

TerminalRenderer::TerminalRenderer():
    ostream_(std::cout)
{}

void TerminalRenderer::renderBoard(const Board<CellView>& board) {
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

char TerminalRenderer::renderCell(CellView cell) {
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
