#pragma once

#include <ostream>

#include "ui.h"

class TextUI final: public UI {
public:
    TextUI();

    void promptForNextPlayer(Player player) override;
    void renderBoard(const Board<CellView>& board, Player player) override;
    Position getMove(Player player) override;
    void indicateResult(PlaceResult r) override;
    void indicateGameOver(Player winner) override;

private:
    std::ostream& ostream_;
};
