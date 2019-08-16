#pragma once

#include <ostream>

#include "renderer.h"

class TerminalRenderer final: public Renderer {
public:
    TerminalRenderer();

    void renderBoard(const Board<CellView>& board) override;

    static char renderCell(CellView cell);

private:
    std::ostream& ostream_;
};
