#include "GridLogic.h"
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std::string_literals;

enum class Control {
    ArrowUp,
    ArrowDown,
    ArrowRight,
    ArrowLeft,
    Delete,
    Command
};

const std::unordered_map<std::string, Control> controlCodes = {
    { "\e[A"s, Control::ArrowUp },
    { "\e[B"s, Control::ArrowDown },
    { "\e[C"s, Control::ArrowRight },
    { "\e[D"s, Control::ArrowLeft },
    { "\e[3~"s, Control::Delete },
    { "\e:"s, Control::Command }
};

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
    std::string escapeSequence = "\e";
    auto code = controlCodes.end();
    do {
        char c;
        input.get(c);
        // reset if char is the escape again
        if(c == '\e') {
            escapeSequence.clear();
        }
        escapeSequence += c;
        code = controlCodes.find(escapeSequence);
    } while(code == controlCodes.end());
    if(code != controlCodes.end()) {
        switch(code->second) {
            case Control::ArrowUp:
                disp.addCursorPos(0, -1);
                break;
            case Control::ArrowDown:
                disp.addCursorPos(0, 1);
                break;
            case Control::ArrowRight:
                disp.addCursorPos(1, 0);
                break;
            case Control::ArrowLeft:
                disp.addCursorPos(-1, 0);
                break;
            case Control::Delete:
                disp.setDisplayPixel(' ');
                break;
            case Control::Command:
                ;
                break;
            default:
                ;
        }
    }
}
