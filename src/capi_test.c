#include <stdio.h>

#include "capi.h"

static const unsigned SIDE_SIZE = 5;

static void TestPlaceTendril(TendrilGame* game) {
    for (unsigned row = 0; row < SIDE_SIZE; ++row) {
        for (unsigned col = 0; col < SIDE_SIZE; ++col) {
            struct TendrilCellPosition pos = {
                .col = col,
                .row = row,
            };

            enum TendrilPlaceResult result = PlaceTendril(
                    game,
                    TENDRIL_COLOR_BLUE,
                    pos);

            switch (result) {
            default:
            case NO_CHANGE:
                printf("no change\n");
                break;
            case TENDRIL_PLACED:
                printf("placed tendril\n");
                break;
            case DESTROYED_TENDRIL:
                printf("destroyed tendril\n");
                break;
            case DESTROYED_CORTEX:
                printf("destroyed cortex\n");
                break;
            }
        }
    }
}

int main(void) {
    TendrilGame* game = NewTendrilGame(SIDE_SIZE);

    TestPlaceTendril(game);

    FreeTendrilGame(game);

    return 0;
}
