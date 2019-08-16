#pragma once

#include "board.h"
#include "cellview.h"

class Renderer {
public:
    Renderer() = default;
    Renderer(const Renderer&) = default;
    Renderer(Renderer&&) = default;
    Renderer& operator=(const Renderer&) = default;
    Renderer& operator=(Renderer&&) = default;
    virtual ~Renderer();

    virtual void renderBoard(const Board<CellView>& board) = 0;
};
