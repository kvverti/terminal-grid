#include "GridInput.h"
#include <istream>

GridInput::GridInput(std::istream& input):
        input(input),
        mode(Mode::Input) { }

char GridInput::getChar() {
    char c;
    input.get(c);
    return c;
}

void GridInput::setMode(Mode mode) {
    this->mode = mode;
}
