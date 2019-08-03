#pragma once

#include <string>

using namespace std;

static constexpr size_t BOARD_SIZE = 20;
static constexpr size_t TOTAL_CELLS = BOARD_SIZE * BOARD_SIZE;

char columnName(unsigned col) {
    return 'A' + col;
}

string rowName(unsigned row) {
    return to_string(row + 1);
}

enum class Player {
    Red,
    Blue,
};

class Board {
public:
    class Square {
    public:
        enum class State: uint8_t {
            Unknown,
            Empty,
            Red,
            Blue,
            RedCortex,
            BlueCortex,
        };

        State state;
    };

    enum class PlaceResult {
        OK,
        Hit,
        HitCortex,
    };

    PlaceResult PlaceTendril(Player player, unsigned x, unsigned y);

private:
    void killSeveredCells();
    Square& squareAt(unsigned x, unsigned y);
    std::array<Square, TOTAL_CELLS> m_squares;
};

constexpr size_t offset(unsigned x, unsigned y) {
    return x * BOARD_SIZE + y;
}

Square& Board::squareAt(unsigned x, unsigned y) {
    return m_squares[offset(x, y)];
}

// FIXME: Pass in existing okCells to avoid an infinite loop.
static bitset<TOTAL_CELLS> reachableCells(const std::array<Square, TOTAL_CELLS>& squares, Player player, unsigned startX, unsigned startY) {
    bitset<TOTAL_CELLS> okCells;

    if (player == Red && squareAt(startX, startY).state == Red) {
        if (okCells[offset(startX, startY)] == true)
            return okCells; // Already processed this cell

        okCells[offset(startX, startY)] = true;
    } else {
        return okCells; // this cell not a matching color. stop looking from here.
    }

    if (startX > 0)
        okCells |= reachableCells(startX - 1, startY);
    if (startY > 0)
        okCells |= reachableCells(startX, startY - 1);
    if (startX < BOARD_SIZE - 1)
        okCells |= reachableCells(startX + 1, startY);
    if (startY < BOARD_SIZE - 1)
        okCells |= reachableCells(startX, startY + 1);

    return okCells;
}

static void clearDeadCells(std::array<Square, TOTAL_CELLS>& squares, bitset<TOTAL_CELLS> okCells) {
    for (size_t i = 0; i < TOTAL_CELLS; ++i) {
        if (okCells[i] == false) {
            squares[i].state = State::Empty;
        }
    }
}

void Board::killSeveredCells(unsigned redCortexX, unsigned redCortexY, unsigned blueCortexX, unsigned blueCortexY) {
    bitset<TOTAL_CELLS> okCells;
    okCells |= reachableCells(m_squares, redCortexX, redCortexY);
    okCells |= reachableCells(m_squares, blueCortexX, blueCortexY);
    clearDeadCells(m_squares, okCells);
}
