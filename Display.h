#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>
#include <string>
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
    std::string& command();

private:
    std::vector<char> display;
    std::ostream& output;
    std::string commandBuffer;
    std::string::size_type oldCommandLen;
    int posX;
    int posY;
    int width;
    int height;
};

#endif
