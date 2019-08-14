#pragma once

#include "board.h"
#include "cell.h"
#include "cellview.h"
#include "player.h"

Board<CellView> makeBoardView(const Board<Cell>& board, Player player);
