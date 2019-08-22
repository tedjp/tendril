#pragma once

#include "board.h"

#ifdef _MSC_VER
# define DLLEXPORT __declspec(dllexport)
#else
// GCC
// (Although this needs -fvisibility=hidden or a pragma push of visibility("hidden"))
# define DLLEXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void TendrilGame;

// This can indicate player color or cell color.
// As of this writing it's only ever used for player color (player ID).
enum TendrilColor {
	TENDRIL_COLOR_NONE = 0x00,
	TENDRIL_COLOR_RED = 0x01,
	TENDRIL_COLOR_BLUE = 0x02,
};

enum TendrilCellContent {
	CONTENT_EMPTY = 0x00,
	CONTENT_TENDRIL = 0x10,
	CONTENT_CORTEX = 0x20,
};

struct TendrilCellPosition {
	unsigned col, row;
};

enum TendrilPlaceResult {
	TENDRIL_PLACED,
	DESTROYED_TENDRIL,
	DESTROYED_CORTEX,
};

// Initialize a new game with randomly-placed cortexes.
DLLEXPORT
TendrilGame* NewTendrilGame(unsigned sideSize);

// Free game resources.
DLLEXPORT
void FreeTendrilGame(TendrilGame* game);

// Retrieve a player's view of the game board.
// Returns an array of cells (row by row) and their contents;
// one of the TendrilCellContent values.
// Does *not* indicate the color, since only cells visible to the requested
// player are returned.
DLLEXPORT
const uint8_t* TendrilGameView(TendrilGame* game, TendrilColor playerColor);

// Place a tendril for the given player at the given location.
DLLEXPORT
TendrilPlaceResult PlaceTendril(
	TendrilGame* game,
	TendrilColor playerColor,
	TendrilCellPosition position);

#ifdef __cplusplus
} // extern "C"
#endif
