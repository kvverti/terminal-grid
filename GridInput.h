#ifndef GRID_INPUT_H
#define GRID_INPUT_H
#include <iosfwd>

class GridInput {
public:
    enum class Mode {
        Input,
        Command
    };

    explicit GridInput(std::istream& input);
    GridInput(const GridInput&) = delete;
    GridInput(GridInput&&) = delete;

    char getChar();
    void setMode(Mode mode);

private:
    std::istream& input;
    Mode mode;
};

#endif
