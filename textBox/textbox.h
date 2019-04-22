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

    TextBox(short width, short top, short left);

    void draw();

    void handleKeyboardEvent(KEY_EVENT_RECORD&);
    void handleKeyboardEvent(MOUSE_EVENT_RECORD&);
};