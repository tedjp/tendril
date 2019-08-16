#pragma once

#include "board.h"
#include "cellview.h"
#include "player.h"

class Renderer {
public:
    Renderer() = default;
    Renderer(const Renderer&) = default;
    Renderer(Renderer&&) = default;
    Renderer& operator=(const Renderer&) = default;
    Renderer& operator=(Renderer&&) = default;
    virtual ~Renderer() = default;

    virtual void renderBoard(const Board<CellView>& board, Player player) = 0;
    virtual void promptForNextPlayer(Player player);
};
