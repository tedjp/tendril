#pragma once

#include <ostream>

enum class Player {
    Blue,
    Red,
};

std::ostream& operator<<(std::ostream& os, Player player);
