#pragma once

#include <ostream>

#include "playerview.h"

class StdoutRenderer {
public:
    static void renderBoard(const Board<CellView>& board, std::ostream& outStream) {
        const unsigned sideSize = board.getSideSize();

        char rendered[sideSize * (sideSize + 1)]; // row x (col + newline)
        char *out = rendered;

        for (unsigned row = 0; row < sideSize; ++row) {
            for (unsigned col = 0; col < sideSize; ++col) {
                *out++ = renderCell(board.cellAt(Position(row, col)));
            }

            *out++ = '\n';
        }

        outStream.write(rendered, sizeof(rendered));
    }

    static char renderCell(CellView cell) {
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

};
