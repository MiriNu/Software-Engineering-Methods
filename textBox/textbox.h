#include <string>
#include <windows.h>
#include "Control.h"

class TextBox : public Control{ 
public:
    COORD currentCoord;

    std::string value;
    short oldWidth;
    TextBox(short width, short top, short left);

    void draw();

    void handleMouseEvent(MOUSE_EVENT_RECORD&);
    void handleKeyboardEvent(KEY_EVENT_RECORD&);
};