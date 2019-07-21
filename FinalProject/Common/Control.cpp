#include "Control.h"
#include "Border/NullBorder.h"

Control* Control::focusedControl = nullptr;

Control::Control() : left(0), top(0), width(1), height(1), textColor(Color::White), backgroundColor(Color::Black) {
    border = new NullBorder;
}

Control::Control(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    left(left), top(top), width(width), height(height), border(border), textColor(textColor), backgroundColor(backgroundColor) {}

Control::~Control() {
    if(border) {
        delete border;
    }
}

void Control::setFocus(Control& control) {
    if((focusedControl != &control) && (control.canGetFocus())) {
        focusedControl = &control;
    }
}

void Control::setBorder(Border* border) {
    if(this->border) {
        delete this->border;
    }
    this->border = border;
}

void Control::draw(Graphics& g, int x, int y, size_t z) {
    int borderPadding = 2;
    g.setForeground(getTextColor());
    g.setBackground(getBackgroundColor());
    border->drawBorder(g,  x, y, width + borderPadding, height + borderPadding);
}
