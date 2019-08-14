#pragma once

#include "board.h"
#include "cell.h"
#include "player.h"

enum class PlaceResult {
    Placed,
    DestroyedTendril,
    DestroyedCortex,
};

class Game {
public:
    //explicit Game(Board<Cell>&& board);
    explicit Game(unsigned size);

    PlaceResult placeTendril(Player player, Position position);

private:
    void killSeveredCells();

    Board<Cell> board_;
    Position blueCortex_, redCortex_;
};
