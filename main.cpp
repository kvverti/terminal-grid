#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "GridLogic.h"

void setupStdin() {
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(1, TCSANOW, &term);
}

int main() {
    GridLogic grid;
    setupStdin();
    // disp.update();
    while(true) {
        grid.tick();
    }
}
