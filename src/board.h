#pragma once

#include <functional>
#include <vector>

class Position final {
public:
    constexpr Position(unsigned col, unsigned row):
        col_(col),
        row_(row)
    {}

    constexpr unsigned col() const {
        return col_;
    }

    constexpr unsigned row() const {
        return row_;
    }

private:
    unsigned col_, row_;
};

template <typename CellT>
class Board {
public:
    using Cell = CellT;

    class Row {
        Row(Board& board, unsigned number):
            num_(number),
            board_(board)
        {}

        CellT& operator[](unsigned row) {
            return board_.cellAt(Position(num_, row));
        }

    private:
        unsigned num_;
        Board<CellT>& board_;
    };

    Board(unsigned side_size):
        side_size_(side_size),
        cells_(side_size * side_size)
    {}

    CellT& cellAt(Position pos) {
        return cells_.at(pos.row() * side_size_ + pos.col());
    }

    Row operator[](unsigned row) {
        return Row(*this, row);
    }

    unsigned getSideSize() const {
        return side_size_;
    }

    // FIXME: Delete duplication of this and function above
    unsigned sideSize() const {
        return side_size_;
    }

    unsigned numCells() const {
        return cells_.size();
    }

    void forEachCell(std::function<void(Cell&, Position)> callback) {
        const auto maxSide = getSideSize();

        for (unsigned row = 0; row < maxSide; ++row) {
            for (unsigned col = 0; col < maxSide; ++col) {
                Position pos(col, row);
                callback(cellAt(pos), pos);
            }
        }
    }

private:
    unsigned side_size_;
    std::vector<CellT> cells_;
};
