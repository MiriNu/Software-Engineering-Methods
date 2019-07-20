#include <string>
#include <windows.h>
#include "../Common/Control.h"

class TextBox : public Control{ 
public:
    COORD currentCoord;

    std::string value;
    short oldWidth;
    TextBox(short width, short top, short left);

    void draw(Graphics& g, int x, int y, size_t z);
    bool canGetFocus(){ return true; }
    void mousePressed(int x, int y, bool isLeft);
    void keyDown(int keyCode, char character);
};