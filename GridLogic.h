#ifndef GRID_LOGIC_H
#define GRID_LOGIC_H
#include "Display.h"

class GridLogic {
public:
    GridLogic();

    void tick();

private:
    Display disp;
    std::istream& input;

    void handleEscape();
};

#endif
