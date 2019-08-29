#pragma once

#include "board.h"

class Game;
class UI;

class Engine {
public:
    void run(Game& game, UI& ui);
};
