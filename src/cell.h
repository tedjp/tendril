#include <cstdint>

#pragma once

class Cell {
public:
    enum class State: uint8_t {
        Empty,
        RedTendril,
        BlueTendril,
        RedCortex,
        BlueCortex,
    };

    Cell() = default;

    State getState() const { return state_; }
    void setState(State state) { state_ = state; }
    void clear() { setState(State::Empty); }

private:
    State state_ = State::Empty;
};
