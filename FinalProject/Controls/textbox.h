#pragma once
#include <string>
#include "../Common/Control.h"
#include "Label.h"
#include "../Common/Graphics.h"
#include "../Common/Border/SingleBorder.h"
#include <iostream>
#include <stdlib.h>

class TextBox : public Label{ 

public:
    COORD currentCoord;

    short oldWidth;
    TextBox(short width, short top, short left);

    void draw(Graphics& g, int x, int y, size_t z);
    bool canGetFocus(){ return true; }
    void mousePressed(int x, int y, bool isLeft);
    void keyDown(int keyCode, char character);
    void setText(string text){ value = text; }
    string getText() { return value; }
};