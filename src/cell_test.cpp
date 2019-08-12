#include <cassert>

#include "cell.h"

using namespace std;

int main(void) {
    Cell c;

    assert(c.getState() == Cell::State::Empty);

    return 0;
}
