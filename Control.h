#ifndef CONTROL_H
#define CONTROL_H
#include "Display.h"
#include <string>
#include <unordered_map>

using Control = void(*)(Display&);

extern const std::unordered_map<std::string, Control> controlCodes;

#endif
