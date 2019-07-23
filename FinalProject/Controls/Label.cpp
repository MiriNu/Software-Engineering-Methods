#include "Label.h"
#include <iostream>

Label::Label(short left, short top, short width, Border* border, Color textColor, Color backgroundColor, string value) :
    Control(left, top, width, 1, border, textColor, backgroundColor), value(value) {};

string Label::getValue() {
    return this->value;
}

void Label::setValue(string value) {
    this->value = value;
}

void Label::draw(Graphics& g, int x, int y, size_t z) {
    if (z == 0) {
        Control::draw(g, x, y, z);
        g.write(x + 1, y + 1, value);
    }
}
