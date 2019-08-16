#pragma once

#include "board.h"
#include "cell.h"
#include "player.h"

enum class PlaceResult {
    Placed,
    DestroyedTendril,
    DestroyedCortex,
};

Position positionFromAlpha(char col, char row);

class Renderer;

class Game {
public:
    using GetMoveCB = Position(*)(Player);

    // Random starting positions
    Game(Renderer *const renderer, Board<Cell>&& board, GetMoveCB getMoveCB);
    // Specific starting positions
    Game(Renderer *const renderer, Board<Cell>&& board, Position blueCortex, Position redCortex, GetMoveCB getMoveCB);

    bool isValidMove(Player player, Position position) const;

    PlaceResult placeTendril(Player player, Position position);

    void run();

private:
    void initializeBoard();
    void killSeveredCells();
    void renderFor(Player whom) const;

    Renderer* renderer_;
    Board<Cell> board_;
    Position blueCortex_, redCortex_;
    GetMoveCB getMoveCB_;
};
