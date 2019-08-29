#include <algorithm>
#include <stdexcept>

#include "game.h"
#include "playerview.h"

using namespace std;

namespace {

using GameBoard = Board<Cell>;

static bool playerHoldsCell(Player player, Cell cell) {
    if (player == Player::Blue)
        return cell.isBlue();
    else if (player == Player::Red)
        return cell.isRed();
    else
        return false;
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
    if (startPosition.col() < board.getSideSize() - 1)
        markCellsReachableByPlayer(board, player, okCells, Position(startPosition.col() + 1, startPosition.row()));
    if (startPosition.row() < board.getSideSize() - 1)
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

Game::Game(Board<Cell>&& board, Position blueCortex, Position redCortex):
    board_(std::move(board)),
    blueCortex_(blueCortex),
    redCortex_(redCortex)
{
    initializeBoard();
}

Game::Game(Board<Cell>&& board):
	board_(move(board)),
	blueCortex_(randomPosition(board.getSideSize())),
	redCortex_(randomPosition(board.getSideSize()))
{
	initializeBoard();
}

void Game::initializeBoard() {
	if (blueCortex_ == redCortex_)
		reassignCortexes();

    Cell& blueCortexCell = board_.cellAt(blueCortex_);
    Cell& redCortexCell = board_.cellAt(redCortex_);

    blueCortexCell.setState({Cell::Content::Cortex, Cell::Color::Blue});
    redCortexCell.setState({Cell::Content::Cortex, Cell::Color::Red});
}

void Game::reassignCortexes() {
	pair<Position, Position> newCortexes = getStartPositions(board_.getSideSize());
	blueCortex_ = newCortexes.first;
	redCortex_ = newCortexes.second;
}

// static
bool Game::qualifiesForAnotherTurn(PlaceResult placeResult) {
	return placeResult == PlaceResult::NoChange
		|| placeResult == PlaceResult::DestroyedTendril;
}

// static
Player Game::playerAfter(Player player) {
	if (player == Player::Blue)
		return Player::Red;
	else
		return Player::Blue;
}

void Game::killSeveredCells() {
    vector<bool> okCells;
    okCells.resize(board_.numCells());

    markCellsReachableByPlayer(board_, Player::Red, okCells, redCortex_);
    markCellsReachableByPlayer(board_, Player::Blue, okCells, blueCortex_);

    clearDeadCells(board_, okCells);
}

namespace {
bool canPlaceTendril(Player player, Cell c) {
    if (c.isEmpty())
        return true;

    if (c.getColor() == Cell::Color::Red && player == Player::Blue)
        return true;

    if (c.getColor() == Cell::Color::Blue && player == Player::Red)
        return true;

    return false;
}

bool colorMatch(Cell::Color cc, Player pc) {
    return    (cc == Cell::Color::Red && pc == Player::Red)
           || (cc == Cell::Color::Blue && pc == Player::Blue);
}
}

bool Game::isValidMove(Player player, Position position) const {
    if (!board_.inRange(position))
        return false;

    bool ok = canPlaceTendril(player, board_.cellAt(position));
    if (!ok)
        return false;

    // Ensure there is connective tissue
    vector<Position> adjacent = board_.positionsAround(position);

    for (Position p: adjacent) {
        if (colorMatch(board_.cellAt(p).getColor(), player)) {
            return true;
        }
    }

    return false;
}

Position positionFromAlpha(char col, char row) {
    char origCol = col;

    if (col >= 'A' && col <= 'Z')
        col = 'a' + (col - 'A');
    if (col >= '0' && col <= '9')
        col = 'a' + (col - '0') - 1;

    if (col < 'a' || col > 'z')
        throw runtime_error(string("Column ") + origCol + " out of range");

    if (row < '0' || row > '9')
        throw runtime_error(string("Row ") + row + " out of range");

    return Position(static_cast<unsigned>(col - 'a'), static_cast<unsigned>(row - '0') - 1);
}

namespace {
bool playerColorMatchesCell(Player player, Cell cell) {
	return (cell.getColor() == Cell::Color::Red && player == Player::Red)
		|| (cell.getColor() == Cell::Color::Blue && player == Player::Blue);
}
}

PlaceResult Game::placeTendril(Player player, Position position) {
    if (!isValidMove(player, position))
        return PlaceResult::NoChange;
        
    Cell& cell = board_.cellAt(position);

	if (playerColorMatchesCell(player, cell))
		return PlaceResult::NoChange;

    auto result = PlaceResult::Placed;

    if (cell.isTendril())
        result = PlaceResult::DestroyedTendril;
    else if (cell.isCortex())
        result = PlaceResult::DestroyedCortex;

    cell.setState({Cell::Content::Tendril, player == Player::Red ? Cell::Color::Red : Cell::Color::Blue});

    killSeveredCells();

    return result;
}

bool Game::isOver() const {
    return !board_.cellAt(blueCortex_).isBlue() || !board_.cellAt(redCortex_).isRed();
}

Player Game::winner() const {
    if (board_.cellAt(blueCortex_).isRed())
        return Player::Red;
    else if (board_.cellAt(redCortex_).isBlue())
        return Player::Blue;
    else
        throw logic_error("Game is not over yet");
}
