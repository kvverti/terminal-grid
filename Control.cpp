#include "Control.h"

const std::unordered_map<std::string, Control> controlCodes = {
    { "[A", [](GridLogic&, Display& disp) { disp.addCursorPos(0, -1); } },
    { "[B", [](GridLogic&, Display& disp) { disp.addCursorPos(0, 1); } },
    { "[C", [](GridLogic&, Display& disp) { disp.addCursorPos(1, 0); } },
    { "[D", [](GridLogic&, Display& disp) { disp.addCursorPos(-1, 0); } },
    { "[3~", [](GridLogic&, Display& disp) { disp.setDisplayPixel(' '); } },
    { ":", [](GridLogic& g, Display& disp) {
        g.setInputMode(GridLogic::Mode::Command);
        disp.command() = ":";
    } }
};
