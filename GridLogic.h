#ifndef GRID_LOGIC_H
#define GRID_LOGIC_H
#include "Display.h"

class GridLogic {
public:
    enum class Mode {
        Input,
        Command
    };

    GridLogic();

    void tick();
    void setInputMode(Mode mode);

private:
    Display disp;
    std::istream& input;
    Mode mode;

    void handleEscape();
    void tickInput();
    void tickCommand();
};

#endif
