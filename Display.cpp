#include "Display.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std::string_literals;

enum class Control {
    ArrowUp,
    ArrowDown,
    ArrowRight,
    ArrowLeft,
    Delete
};

const std::unordered_map controlCodes = {
    std::make_pair("\e[A"s, Control::ArrowUp),
    std::make_pair("\e[B"s, Control::ArrowDown),
    std::make_pair("\e[C"s, Control::ArrowRight),
    std::make_pair("\e[D"s, Control::ArrowLeft),
    std::make_pair("\e[3~"s, Control::Delete)
};

Display::Display(size_type width, size_type height, std::istream& input, std::ostream& output):
        display(width * height, ' '),
        input(input),
        output(output),
        posX(0),
        posY(0),
        width(width),
        height(height) { }

void Display::update() {
    std::string caps(width + 2, '-');
    output << caps << '\n';
    for(size_type i = 0; i < height; ++i) {
        auto itr = display.begin() + (i * width);
        output << '|';
        if(i == posY) {
            output << std::string { itr, itr + posX }
                << '_' << std::string { itr + posX + 1, itr + width };
        } else {
            output << std::string { itr, itr + width };
        }
        output << '|' << '\n';
    }
    output << caps << '\n';
}

void Display::tick() {
    char c;
    input.get(c);
    switch(c) {
        case '\e':
            handleEscape();
            break;
        case '\177':
            addCursorPos(-1, 0);
            setDisplayPixel(' ');
            break;
        case '\n':
            addCursorPos(0, 1);
            break;
        default:
            setDisplayPixel(c);
            addCursorPos(1, 0);
    }

    for(size_type i = 0; i < height + 2; ++i) {
        output << "\e[A";
    }
    update();
}

void Display::handleEscape() {
    std::string escapeSequence = "\e";
    char c;
    input.get(c);
    escapeSequence += c;
    input.get(c);
    escapeSequence += c;
    if('0' <= c && c <= '9') {
        // continue to get characters until ~
        while(c != '~') {
            input.get(c);
            escapeSequence += c;
        }
    }
    auto code = controlCodes.find(escapeSequence);
    if(code != controlCodes.end()) {
        switch(code->second) {
            case Control::ArrowUp:
                addCursorPos(0, -1);
                break;
            case Control::ArrowDown:
                addCursorPos(0, 1);
                break;
            case Control::ArrowRight:
                addCursorPos(1, 0);
                break;
            case Control::ArrowLeft:
                addCursorPos(-1, 0);
                break;
            case Control::Delete:
                setDisplayPixel(' ');
                break;
            default:
                ;
        }
    }
}

void Display::addCursorPos(diff_type dx, diff_type dy) {
    if((dx < 0 && posX >= dx) || posX + dx < width) {
        posX += dx;
    }
    if((dy < 0 && posY >= dy) || posY + dy < height) {
        posY += dy;
    }
}

void Display::setDisplayPixel(char c) {
    display[posY * width + posX] = c;
}
