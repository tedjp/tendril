#include "player.h"

std::ostream& operator<<(std::ostream& os, Player player) {
    switch (player) {
    case Player::Blue:
        return os << "Blue";
    case Player::Red:
        return os << "Red";
    default:
        return os << "?";
    }
}
