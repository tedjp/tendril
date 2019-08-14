#include "playerview.h"

Board<CellView> makeBoardView(const Board<Cell>& board, Player player) {
    Board<CellView> boardView(board.getSideSize());

    board.forEachCell([&boardView, player](const Cell& cell, Position pos) {
                if (cell.isEmpty())
                    return; // fog of war
                if (player == Player::Red && !cell.isRed())
                    return;
                if (player == Player::Blue && !cell.isBlue())
                    return;

                boardView[pos] =
                      cell.isTendril() ? CellView::State::OurTendril
                    : cell.isCortex() ? CellView::State::OurCortex
                    : CellView::State::Unknown;
            });

    return boardView;
}
