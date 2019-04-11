#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>
#include <iosfwd>

class Display {
public:
    using size_type = std::vector<char>::size_type;
    using diff_type = std::vector<char>::difference_type;

    Display(size_type width, size_type height, std::ostream& output);
    Display(const Display&) = delete;
    Display(Display&&) = delete;

    void update();
    void addCursorPos(diff_type dx, diff_type dy);
    void setDisplayPixel(char c);

private:
    std::vector<char> display;
    std::ostream& output;
    size_type posX;
    size_type posY;
    size_type width;
    size_type height;
};

#endif
