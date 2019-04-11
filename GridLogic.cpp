#include "GridLogic.h"
#include "Control.h"
#include <iostream>

GridLogic::GridLogic():
        disp(20, 10, std::cout),
        input(std::cin) { }

void GridLogic::tick() {
    char c;
    input.get(c);
    switch(c) {
        case '\e':
            handleEscape();
            break;
        case '\177':
            disp.addCursorPos(-1, 0);
            disp.setDisplayPixel(' ');
            break;
        case '\n':
            disp.addCursorPos(-disp.getCursorPos().first, 1);
            break;
        default:
            disp.setDisplayPixel(c);
            disp.addCursorPos(1, 0);
    }
    disp.update();
}

void GridLogic::handleEscape() {
    std::string escapeSequence {};
    auto code = controlCodes.end();
    do {
        char c;
        input.get(c);
        // reset if char is the escape again
        if(c == '\e') {
            escapeSequence.clear();
        } else {
            escapeSequence += c;
            code = controlCodes.find(escapeSequence);
        }
    } while(code == controlCodes.end());
    code->second(disp);
}
