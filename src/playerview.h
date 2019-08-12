#include "board.h"

void MakeBoardView(const Board<Cell>& board, Player player) {
    Board<CellView> boardView(board.getSideSize());

    board.forEachCell([&boardView, player](const Cell& cell, Position pos) {
                if (cell.isEmpty())
                    return; // fog of war
                if (player == Red && !cell.isRed())
                    return;
                if (player == Blue && !cell.isBlue())
                    return;

                boardView[pos] =
                    cell.isTendril() ? CellView::State::OurTendril
                    cell.isCortex() ? CellView::State::OurCortex
                    : CellView::State::Unknown;
            });

    return boardView;
}
