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

class Renderer;

class Game {
public:
	// XXX: Move to Engine
    using GetMoveCB = Position(*)(Player);

    // Random starting positions
	// XXX: Move renderer & getMoveCB to Engine
    Game(Renderer *const renderer, Board<Cell>&& board, GetMoveCB getMoveCB);

    // Specific starting positions
	// XXX: Move renderer & getMoveCB to Engine
    Game(Renderer *const renderer, Board<Cell>&& board, Position blueCortex, Position redCortex, GetMoveCB getMoveCB);

    bool isValidMove(Player player, Position position) const;

    PlaceResult placeTendril(Player player, Position position);

    void run();

	const Board<Cell>& board() const;

	static bool qualifiesForAnotherTurn(PlaceResult placeResult);
	static Player playerAfter(Player player);

private:
    void initializeBoard();
    void reassignCortexes();
    void killSeveredCells();
    void renderFor(Player whom) const;

    Renderer* renderer_;
    Board<Cell> board_;
    Position blueCortex_, redCortex_;
    GetMoveCB getMoveCB_;
};

inline const Board<Cell>& Game::board() const {
	return board_;
}
