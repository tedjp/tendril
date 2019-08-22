#include "capi.h"

#include "board.h"
#include "game.h"
#include "playerview.h"

#include <cassert>
#include <stdexcept>
#include <vector>

using namespace std;

namespace {

// This is the real TendrilGame structure that the C API passes by pointer.
class CTendrilGameState {
public:
	CTendrilGameState(unsigned sideSize);

	Game m_game;
	std::vector<uint8_t> m_playerView;
};

CTendrilGameState::CTendrilGameState(unsigned sideSize) :
	m_game(nullptr, Board<Cell>(sideSize), nullptr),
	m_playerView(sideSize * static_cast<size_t>(sideSize), 0)
{}

uint8_t CellViewToUint8(CellView cellView) {
	switch (cellView.getState()) {
	case CellView::State::OurCortex:
		return CONTENT_CORTEX;
	case CellView::State::OurTendril:
		return CONTENT_TENDRIL;
	case CellView::State::Unknown:
	default:
		return CONTENT_EMPTY;
	}
}

void TranslateBoardViewToVector(const Board<CellView>& view, vector<uint8_t>& vec) {
	const unsigned sideSize = view.getSideSize();

	assert(vec.size() == sideSize);

	for (unsigned i = 0; i < sideSize; ++i) {
		vec[i] = CellViewToUint8(view.cellAt(Position(i % sideSize, i / sideSize)));
	}
}

Player PlayerFromC(TendrilColor color) {
	if (color == TENDRIL_COLOR_BLUE)
		return Player::Blue;
	else
		return Player::Red;
}

Position PositionFromC(TendrilCellPosition cposition) {
	return Position(cposition.col, cposition.row);
}

TendrilPlaceResult PlaceResultToC(PlaceResult placeResult) {
	switch (placeResult) {
	case PlaceResult::Placed:
		return TENDRIL_PLACED;
	case PlaceResult::DestroyedCortex:
		return DESTROYED_CORTEX;
	case PlaceResult::DestroyedTendril:
		return DESTROYED_TENDRIL;
	}

	throw logic_error("Failed to convert from C++ PlaceResult");
}

} // anonymous

TendrilGame* NewTendrilGame(unsigned sideSize) {
	CTendrilGameState* cgame = new CTendrilGameState(sideSize);

	return cgame;
}

void FreeTendrilGame(TendrilGame* game) {
	CTendrilGameState* cgame = reinterpret_cast<CTendrilGameState*>(game);
	delete cgame;
}

Player PlayerFromColor(TendrilColor color) {
	if (color == TENDRIL_COLOR_BLUE)
		return Player::Blue;
	else
		return Player::Red;
}

const uint8_t* TendrilGameView(TendrilGame* game, TendrilColor playerColor) {
	CTendrilGameState* cgame = reinterpret_cast<CTendrilGameState*>(game);

	Board<CellView> playerView = makeBoardView(
		cgame->m_game.board(),
		PlayerFromColor(playerColor));

	TranslateBoardViewToVector(playerView, cgame->m_playerView);

	return cgame->m_playerView.data();
}

TendrilPlaceResult PlaceTendril(
	TendrilGame* game,
	TendrilColor playerColor,
	TendrilCellPosition position)
{
	CTendrilGameState* cgame = reinterpret_cast<CTendrilGameState*>(game);

	return PlaceResultToC(
		cgame->m_game.placeTendril(
			PlayerFromC(playerColor),
			PositionFromC(position)));
}
