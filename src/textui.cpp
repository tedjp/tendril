#include <iostream>
#include <string>

#include "textui.h"

using namespace std;

namespace {

void clearScreen(std::ostream& out) {
    static const std::string newlines(31, '\n');
    out.write(newlines.data(), newlines.size());
}

char renderCell(CellView cell) {
    switch (cell.getState()) {
    case CellView::State::Unknown:
        return ' ';
    case CellView::State::OurCortex:
        return '@';
    case CellView::State::OurTendril:
        return '+';
    default:
        return '?';
    }
}

void printRowSeparator(ostream& out, unsigned cols) {
    out << '+';
    for (unsigned i = 0; i < cols; ++i)
        out << "-+";
    out << '\n';
}

} // anon

TextUI::TextUI():
    ostream_(std::cout)
{}

void TextUI::renderBoard(const Board<CellView>& board, Player player) {
    clearScreen(ostream_);
    ostream_ << player << "'s view:\n";

    const unsigned sideSize = board.getSideSize();

    for (unsigned row = 0; row < sideSize; ++row) {
        printRowSeparator(ostream_, sideSize);

        ostream_ << '|';

        for (unsigned col = 0; col < sideSize; ++col) {
            ostream_ << renderCell(board.cellAt(Position(col, row))) << '|';
        }

        ostream_ << '\n';
    }

    printRowSeparator(ostream_, sideSize);
}

void TextUI::promptForNextPlayer(Player player) {
    clearScreen(ostream_);
    ostream_ << player << "'s turn next, pass the laptop!\n";
    ostream_ << player << " press enter to continue.\n";
    string trash;
    getline(cin, trash);
}

Position TextUI::getMove(Player player) {
    // TODO: ANSI color codes on the prompt
    cout << player << "'s move? ";

    char col, row;

    cin >> col >> row;

    // Throw away newline. maybe unnecessary
    string trash;
    getline(cin, trash);

    return positionFromAlpha(col, row);
}

void TextUI::indicateResult(PlaceResult r) {
    switch (r) {
    case PlaceResult::Placed:
        cout << "OK, you grew your tendril.\n";
        return;
    case PlaceResult::DestroyedTendril:
        cout << "**SMASH** you squashed their tendril\n";
        return;
    case PlaceResult::DestroyedCortex:
        cout << "Squelch. That was the CORTEX. You win!\n";
        return;
    default:
        cerr << "Shit's broken, yo.\n";
        return;
    }
}

void TextUI::indicateGameOver(Player winner) {
    cout << winner << " wins!\n";
}
