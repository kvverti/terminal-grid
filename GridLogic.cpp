#include "GridLogic.h"
#include "Control.h"
#include <iostream>

GridLogic::GridLogic():
        disp(20, 10, std::cout),
        input(std::cin),
        mode(Mode::Input) { }

void GridLogic::tick() {
    switch(mode) {
        case Mode::Input:
            tickInput();
            break;
        case Mode::Command:
            tickCommand();
            break;
    }
}

void GridLogic::tickInput() {
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

void GridLogic::tickCommand() {
    char c;
    input.get(c);
    std::string& command = disp.command();
    switch(c) {
        case '\e':
            // do nothing
            break;
        case '\177':
            if(command.size() > 1) {
                command.pop_back();
            }
            break;
        case '\n':
            // newline swaps input mode back
            setInputMode(Mode::Input);
            command.clear();
            break;
        default:
            command += c;
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
    code->second(*this, disp);
}

void GridLogic::setInputMode(Mode mode) {
    this->mode = mode;
}
