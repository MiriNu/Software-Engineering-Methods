#include "Label.h"
#include <iostream>

Label::Label(string value) : Control(), value(value) {};

Label::Label(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor, string value) :
    Control(left, top, width, height, border, textColor, backgroundColor), value(value) {};

string Label::getValue() {
    return this->value;
}

void Label::setValue(string value) {
    this->value = value;
}

void Label::draw(Graphics& g, int x, int y, size_t z) {
    if (z == 0) {
        Control::draw(g, x, y, z);
        g.write(x, y, value);
    }
}
