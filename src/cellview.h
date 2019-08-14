#pragma once

#include <cstdint>

// A player's view of a cell.
class CellView {
public:
    enum class State: uint8_t {
        Unknown, // fog-of-war. Not the same as empty.
        OurCortex,
        OurTendril,
    };

    CellView() = default;
    CellView(State state): state_(state) {}

    State getState() const {
        return state_;
    }

private:
    State state_ = State::Unknown;
};
