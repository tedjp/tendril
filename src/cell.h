#include <cstdint>

#pragma once

class Cell {
public:
    enum class Color: uint8_t {
        None,
        Red,
        Blue,
    };

    enum class Content: uint8_t {
        Empty,
        Tendril,
        Cortex,
    };

    struct State {
        Content content;
        Color color;
    };

    Cell();

    Color getColor() const { return static_cast<Color>(color_); }
    Content getContent() const { return static_cast<Content>(content_); }
    State getState() const { return State{getContent(), getColor()}; }

    bool isEmpty() const { return static_cast<Content>(content_) == Content::Empty; }
    // This might be excessive
    bool isRed() const { return static_cast<Color>(color_) == Color::Red; }
    bool isBlue() const { return static_cast<Color>(color_) == Color::Blue; }
    bool isTendril() const { return static_cast<Content>(content_) == Content::Tendril; }
    bool isCortex() const { return static_cast<Content>(content_) == Content::Cortex; }

    void setState(State state) {
        content_ = static_cast<unsigned>(state.content);
        color_ = static_cast<unsigned>(state.color);
    }

    void clear();

private:
    unsigned color_: 2;
    unsigned content_: 2;
};
