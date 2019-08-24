#include "capi.h"

int main(void) {
    TendrilGame* game = NewTendrilGame(5);
    FreeTendrilGame(game);

    return 0;
}
