#include "engine.h"
#include "game.h"
#include "playerview.h"
#include "ui.h"

namespace {
void render(Player forWhom, const Board<Cell>& board, UI& ui) {
    ui.renderBoard(makeBoardView(board, forWhom), forWhom);
}
} // anon

void Engine::run(Game& game, UI& ui) {
    // TODO: Randomize first player.
    Player player = Player::Blue;
    PlaceResult placeResult = PlaceResult::NoChange;

    while (!game.isOver()) {
        if (!game.qualifiesForAnotherTurn(placeResult)) {
            player = game.playerAfter(player);
            ui.promptForNextPlayer(player);
        }

        render(player, game.board(), ui);

        Position position(0, 0);
        do {
            position = ui.getMove(player);
        } while (!game.isValidMove(player, position));

        placeResult = game.placeTendril(player, position);
        ui.indicateResult(placeResult);
    }

    ui.indicateGameOver(game.winner());
}
