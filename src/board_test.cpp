#include <cassert>

#include "board.h"

namespace {

struct MyCell {
};

void TestBoard() {
#if 0
    // Throws...
    Board(-1);
    Board(0);
#endif

    Board<MyCell> board(1);
    // Test: board(ceil(sqrt(2^32-1))) (should throw)
}

} // anon

int main(void) {
    TestBoard();
}
