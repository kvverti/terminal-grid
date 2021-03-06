#include "Display.h"
#include <ostream>
#include <utility>

Display::Display(int width, int height, std::ostream& output):
        display(width * height, ' '),
        output(output),
        commandBuffer(),
        oldCommandLen(0),
        posX(0),
        posY(0),
        width(width),
        height(height) { }

std::pair<int, int> Display::getCursorPos() const {
    return { posX, posY };
}

std::string& Display::command() {
    return commandBuffer;
}

void Display::update() {
    std::string caps(width + 2, '-');
    // reset position
    output << '\r';
    for(int i = 0; i < height + 2; ++i) {
        output << "\e[A";
    }
    output << caps << '\n';
    for(int i = 0; i < height; ++i) {
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
    output << caps << '\n' << std::string(oldCommandLen, ' ')
        << '\r' << commandBuffer;
    oldCommandLen = commandBuffer.size();
}

void Display::addCursorPos(int dx, int dy) {
    if((dx >= 0 || posX >= -dx) && posX < width - dx) {
        posX += dx;
    }
    if((dy >= 0 || posY >= -dy) && posY < height - dy) {
        posY += dy;
    }
}

void Display::setDisplayPixel(char c) {
    display[posY * width + posX] = c;
}
