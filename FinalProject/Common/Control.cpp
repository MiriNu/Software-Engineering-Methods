#include "Control.h"
#include "Border/NullBorder.h"
#include "../Controls/MessageBox.h"

Control* Control::focusedControl = nullptr;
bool Control::messageBoxLock = false;

Control::Control(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    left(left), top(top), width(width), height(height), border(border), textColor(textColor), backgroundColor(backgroundColor) {}

Control::~Control() {
    if(border) {
        delete border;
    }
}

void Control::setFocus(Control& control) {
    if((focusedControl != &control) && (control.canGetFocus() || (typeid(control) == typeid(semMessageBox)))) {
        focusedControl = &control;
    }
}

void Control::setMessageBoxLock(bool isLocked) {
    messageBoxLock = isLocked;
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
    g.setCursorVisibility(false);
    border->drawBorder(g,  x, y, width + borderPadding, height + borderPadding);
}
