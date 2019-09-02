#pragma once

#include "board.h"
#include "cell.h"
#include "player.h"

enum class PlaceResult {
	NoChange, // played on an existing owned location
    Placed,
    DestroyedTendril,
    DestroyedCortex,
};

Position positionFromAlpha(char col, char row);

class Game {
public:
    // Random starting positions
    Game(Board<Cell>&& board);

    // Specific starting positions
    Game(Board<Cell>&& board, Position blueCortex, Position redCortex);

    bool isValidMove(Player player, Position position) const;

    PlaceResult placeTendril(Player player, Position position);

	const Board<Cell>& board() const;

	static bool qualifiesForAnotherTurn(PlaceResult placeResult);
	static Player playerAfter(Player player);

    bool isOver() const;
    Player winner() const; // throws unless isOver() == true

private:
    void initializeBoard();
    void reassignCortexes();
    void killSeveredCells();

    Board<Cell> board_;
    Position blueCortex_, redCortex_;
};

inline const Board<Cell>& Game::board() const {
	return board_;
}
