#include "cell.h"

Cell::Cell():
    color_(static_cast<unsigned>(Color::None)),
    content_(static_cast<unsigned>(Content::Empty))
{}

void Cell::clear() {
    color_ = static_cast<unsigned>(Color::None);
    content_ = static_cast<unsigned>(Content::Empty);
}
