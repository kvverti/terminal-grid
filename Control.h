#ifndef CONTROL_H
#define CONTROL_H
#include "Display.h"
#include "GridLogic.h"
#include <string>
#include <unordered_map>

using Control = void(*)(GridLogic&, Display&);

extern const std::unordered_map<std::string, Control> controlCodes;

#endif
