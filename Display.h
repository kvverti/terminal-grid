#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>
#include <iosfwd>

class Display {
public:
    Display(int width, int height, std::ostream& output);
    Display(const Display&) = delete;
    Display(Display&&) = delete;

    std::pair<int, int> getCursorPos() const;

    void update();
    void addCursorPos(int dx, int dy);
    void setDisplayPixel(char c);

private:
    std::vector<char> display;
    std::ostream& output;
    int posX;
    int posY;
    int width;
    int height;
};

#endif
