#pragma once

#include <string>

#include "board.h"
#include "cell.h"

Board<Cell> loadBoard(const std::string& filename);
