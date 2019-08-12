#include "game.h"

using namespace std;

namespace {

using GameBoard = Board<Cell>;

// XXX: Refactor so cell is empty/red/blue regardless of state.
static bool isRed(const Cell& c) {
    auto state = c.getState();
    return state == Cell::State::RedTendril || state == Cell::State::RedCortex;
}

static bool isBlue(const Cell& c) {
    auto state = c.getState();
    return state == Cell::State::BlueTendril || state == Cell::State::BlueCortex;
}

static bool playerHoldsCell(Player player, Cell cell) {
    if (player == Player::Blue)
        return isBlue(cell);
    else
        return isRed(cell);
}

static unsigned okCellsOffset(unsigned sideSize, Position position) {
    return position.row() * sideSize + position.col();
}

static void markCellsReachableByPlayer(GameBoard& board, Player player, vector<bool>& okCells, Position startPosition) {
    if (playerHoldsCell(player, board.cellAt(startPosition))) {
        if (okCells[okCellsOffset(board.getSideSize(), startPosition)] == true)
            return; // Already processed this cell.

        okCells[okCellsOffset(board.getSideSize(), startPosition)] = true;
    } else {
        return; // this cell not a matching color. stop looking from here.
    }

    // Parallelize?
    if (startPosition.col() > 0)
        markCellsReachableByPlayer(board, player, okCells, Position(startPosition.col() - 1, startPosition.row()));
    if (startPosition.row() > 0)
        markCellsReachableByPlayer(board, player, okCells, Position(startPosition.col(), startPosition.row() - 1));
    if (startPosition.col() < board.sideSize() - 1)
        markCellsReachableByPlayer(board, player, okCells, Position(startPosition.col() + 1, startPosition.row()));
    if (startPosition.row() < board.sideSize() - 1)
        markCellsReachableByPlayer(board, player, okCells, Position(startPosition.col(), startPosition.row() + 1));
}

static void clearDeadCells(GameBoard& board, vector<bool> okCells) {
    board.forEachCell(
            [&okCells, sideSize = board.getSideSize()](Cell& cell, Position position) {
                if (okCells[okCellsOffset(sideSize, position)] == false)
                    cell.clear();
            });
}

} // anon

Game::Game(unsigned boardSize):
    board_(boardSize),
    blueCortex_(0, 0),
    redCortex_(9, 9)
{}

void Game::killSeveredCells() {
    vector<bool> okCells;
    okCells.resize(board_.numCells());

    markCellsReachableByPlayer(board_, Player::Red, okCells, redCortex_);
    markCellsReachableByPlayer(board_, Player::Blue, okCells, blueCortex_);

    clearDeadCells(board_, okCells);
}
