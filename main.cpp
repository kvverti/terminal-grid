#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "Display.h"

void setupStdin() {
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(1, TCSANOW, &term);
}

Display disp { 20, 10, std::cin, std::cout };

int main() {
    setupStdin();
    disp.update();
    while(true) {
        disp.tick();
    }
}
