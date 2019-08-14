#include "boardloader.h"

#include <fstream>
#include <istream>
#include <stdexcept>

// File format:
// ascii representation of board
// cell contents:
// (space): empty
// X: Red Cortex
// x: Blue Cortex
// T: Red Tendril
// t: Blue Tendril
// example 3x3 where each player is about to find the opponent's cortex
// XTT
// t T
// ttx

using namespace std;

namespace {
Cell::State stateFromChar(char c) {
    switch (c) {
    case 'X':
        return {Cell::Content::Cortex, Cell::Color::Red};
    case 'T':
        return {Cell::Content::Tendril, Cell::Color::Red};
    case 'x':
        return {Cell::Content::Cortex, Cell::Color::Blue};
    case 't':
        return {Cell::Content::Tendril, Cell::Color::Blue};
    default:
        return {Cell::Content::Empty, Cell::Color::None};
    }
}

void setRow(Board<Cell>& board, unsigned rowNum, const string& line) {
    if (line.size() != board.getSideSize()) {
        throw runtime_error(string("Board size does not match line size; "
                    "board_size=" + to_string(board.getSideSize()) + ", line_size="
                    + to_string(line.size()) + ". Check input file."));
    }

    for (unsigned col = 0; col < line.size(); ++col) {
        board.cellAt(Position(col, rowNum)).setState(stateFromChar(line[col]));
    }
}
} // anon

Board<Cell> loadBoard(const string& filename) {
    // Doesn't belong here, but we do want it in main()
    //ios_base::sync_with_stdio(false);

    ifstream in(filename);

    Board<Cell> board(0);

    string line;
    unsigned rowNum = 0;

    while (getline(in, line)) {
        if (rowNum == 0)
            board = Board<Cell>(line.size());

        setRow(board, rowNum, line);
        ++rowNum;
    }

    return board;
}
