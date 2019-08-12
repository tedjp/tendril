#pragma once

#include "board.h"
#include "cell.h"

enum class Player {
    Blue,
    Red,
};

enum class PlaceResult {
    Placed,
    DestroyedTendril,
    DestroyedCortex,
};

class Game {
public:
    explicit Game(unsigned boardSize = 10);

    PlaceResult placeTendril(Player player, Position position);

private:
    void killSeveredCells();

    Board<Cell> board_;
    Position blueCortex_, redCortex_;
};
