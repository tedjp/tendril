#pragma once

#include <ostream>

#include "renderer.h"

class TerminalRenderer final: public Renderer {
public:
    TerminalRenderer();

    void renderBoard(const Board<CellView>& board, Player player) override;
    void promptForNextPlayer(Player player) override;

private:
    std::ostream& ostream_;
};
