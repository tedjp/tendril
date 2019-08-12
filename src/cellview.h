#pragma once

#include <cstdint>

// A player's view of a cell.
class PlayerCellView {
public:
    enum class State: uint8_t {
        Unknown, // fog-of-war. Not the same as empty.
        OurCortex,
        OurTendril,
    };
};
