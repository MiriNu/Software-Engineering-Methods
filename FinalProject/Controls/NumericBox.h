#pragma once
#include "../Common/Control.h"
#include "Button.h"
#include "Label.h"
#include "../Common/Graphics.h"
#include "../Common/Border/SingleBorder.h"
#include "MouseListener.h"

class NumericBox : public Control, public MouseListener {
protected:
    Button add;
    Button subtract;
    Label value;

public:
    NumericBox(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor);
    void draw(Graphics& g, int x, int y, size_t z);
    void mousePressed(int x, int y, bool isLeft);
    void update(int x, int y);
    void addToVal();
    void subFromVal();
};