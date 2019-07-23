#include "Button.h"
#include <iostream>

Button::Button(short left, short top, short width, Border* border, Color textColor, Color backgroundColor, string value) :
    Label(left, top, width, border, textColor, backgroundColor, value) {};

bool Button::addListener(MouseListener *listener) {
    if(listener != nullptr) {
        try {
            listeners.push_back(listener);
        }
        catch(...) {
            return false;
        }
        return true;
    }
    return false;
}

void Button::mousePressed(int x, int y, bool isLeft) {
    int l = getLeft(), t = getTop(), w = getWidth(), h = getHeight();
    if(x >= l && x <= l + w &&  y >= t && y <= t + h && isLeft) {
        for(int i = 0; i < listeners.size(); ++i) {
            listeners[i]->update(x, y);
        }
    }
}