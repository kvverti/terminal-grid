#include "Control.h"

const std::unordered_map<std::string, Control> controlCodes = {
    { "[A", [](Display& disp) { disp.addCursorPos(0, -1); } },
    { "[B", [](Display& disp) { disp.addCursorPos(0, 1); } },
    { "[C", [](Display& disp) { disp.addCursorPos(1, 0); } },
    { "[D", [](Display& disp) { disp.addCursorPos(-1, 0); } },
    { "[3~", [](Display& disp) { disp.setDisplayPixel(' '); } },
    { ":", [](Display& disp) {} }
};
