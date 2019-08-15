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

    const CellT& cellAt(Position pos) const {
        return cells_.at(pos.row() * side_size_ + pos.col());
    }

    CellT& operator[](Position pos) {
        return cellAt(pos);
    }

    Row operator[](unsigned row) {
        return Row(*this, row);
    }

    unsigned getSideSize() const {
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

    void forEachCell(std::function<void(const Cell&, Position)> callback) const {
        const auto maxSide = getSideSize();

        for (unsigned row = 0; row < maxSide; ++row) {
            for (unsigned col = 0; col < maxSide; ++col) {
                Position pos(col, row);
                callback(cellAt(pos), pos);
            }
        }
    }

    bool inRange(Position p) const {
        const unsigned size = getSideSize();
        return p.col() < size && p.row() < size;
    }

    bool inRange(unsigned n) const {
        return n < getSideSize();
    }

    std::vector<Position> positionsAround(Position pos) const {
        std::vector<Position> positions;
        positions.reserve(4);
        // This results in some duplicates but it's OK.
        // (Had to introduce them because the inRange() check wasn't working
        // as desired.)
        const unsigned rows[3] = {pos.row() > 0 ? pos.row() - 1 : 0, pos.row(), pos.row() + 1 < getSideSize() ? pos.row() + 1 : pos.row()};
        const unsigned cols[3] = {pos.col() > 0 ? pos.col() - 1 : 0, pos.col(), pos.col() + 1 < getSideSize() ? pos.col() + 1 : pos.col()};

        for (unsigned ri = 0; ri < 3; ++ri) {
            if (!inRange(rows[ri]))
                continue;

            for (unsigned ci = 0; ci < 3; ++ci) {
                if (!inRange(cols[ci]))
                    continue;

                // Skip self-cell
                if (ci == 1 && ri == 1)
                    continue;

                // Disallow diagonals
                if (ci != 1 && ri != 1)
                    continue;

                positions.emplace_back(cols[ci], rows[ci]);
            }
        }

        //cerr << "legal positions: " << positions << "\n";

        return positions;

    }

    std::vector<std::reference_wrapper<Cell>> cellsAround(Position pos, std::function<bool(Cell)> predicate = [](Cell){ return true; }) {
        std::vector<Position> positions = positionsAround(pos);
        std::vector<std::reference_wrapper<Cell>> cells;
        cells.reserve(positions.size());
        for (Position position: positions) {
            Cell c = cellAt(position);
            if (predicate(c)) {
                cells.emplace_back(std::ref(cellAt(position)));
            }
        }

        return cells;
    }

private:
    unsigned side_size_;
    std::vector<CellT> cells_;
};
