#include "board.h"

#include <random>
#include <stdexcept>

using namespace std;

Position randomPosition(unsigned boardSize) {
	random_device rd;
	uniform_int_distribution<unsigned> distribution(0, boardSize - 1);
	return Position(distribution(rd), distribution(rd));
}

pair<Position, Position> getStartPositions(unsigned boardSize) {
	if (boardSize <= 1)
		throw runtime_error("Cannot find unique positions on a 1x1 board");

	Position first = randomPosition(boardSize);
	Position second = first;
	while (second == first)
		second = randomPosition(boardSize);

	return { first, second };
}
