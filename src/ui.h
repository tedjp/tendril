#pragma once

#include "board.h"
#include "cellview.h"
#include "game.h"
#include "player.h"

class UI {
public:
    UI() = default;
    UI(const UI&) = default;
    UI(UI&&) = default;
    UI& operator=(const UI&) = default;
    UI& operator=(UI&&) = default;
    virtual ~UI() = default;

    virtual void indicateResult(PlaceResult r) {}
    virtual void indicateGameOver(Player winner) = 0;
    virtual void renderBoard(const Board<CellView>& board, Player player) = 0;
    virtual void promptForNextPlayer(Player player) = 0;
    virtual Position getMove(Player player) = 0;

private:
    static const int _vtable_pin;
};
