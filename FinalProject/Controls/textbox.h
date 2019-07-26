#pragma once
#include <string>
#include "../Common/Control.h"
#include "Label.h"
#include "../Common/Graphics.h"
#include "../Common/Border/Border.h"
#include <iostream>
#include <stdlib.h>

class TextBox : public Label{ 

public:
    COORD currentCoord;

    TextBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor);

    void draw(Graphics& g, int x, int y, size_t z);
    bool canGetFocus(){ return true; }
    void mousePressed(int x, int y, bool isLeft);
    void keyDown(int keyCode, char character);
    void setText(string text);
    string getText() { return value; }
};