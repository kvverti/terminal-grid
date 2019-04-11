#include "Display.h"
#include <ostream>

Display::Display(size_type width, size_type height, std::ostream& output):
        display(width * height, ' '),
        output(output),
        posX(0),
        posY(0),
        width(width),
        height(height) { }

void Display::update() {
    std::string caps(width + 2, '-');
    for(size_type i = 0; i < height + 2; ++i) {
        output << "\e[A";
    }
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

void Display::addCursorPos(diff_type dx, diff_type dy) {
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
