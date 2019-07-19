#include <string>
#include <windows.h>

class TextBox{ 
public:
    short width;
    short top;
    short left;
    bool hasBorder;
    WORD color;
    WORD background;
    COORD currentCoord;

    std::string value;
    short oldWidth;
    TextBox(short width, short top, short left);

    void draw();

    void handleMouseEvent(MOUSE_EVENT_RECORD&);
    void handleKeyboardEvent(KEY_EVENT_RECORD&);
};