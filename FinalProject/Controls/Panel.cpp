#include "Panel.h"

Panel::Panel() : Control() {}

Panel::Panel(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    Control(left, top, width, height, border, textColor, backgroundColor) {}

bool Panel::addControl(Control* control) {
    if(control != nullptr) {
        try {
            controls.push_back(control);
            if(getFocus() == nullptr && control->canGetFocus()) {
                setFocus(*control);
            }
        }
        catch(...) {
            return false;
        }
        return true;
    }
    return false;
}

Control* Panel::getControl(int index) {
    if(controls.size() < index || index < 0) {
        return nullptr;
    }
    return controls[index];
}

bool Panel::focusInPanel() {
    Control* tempPtr = getFocus();
    if(getFocus() != nullptr) {
        for(int i = 0; i < controls.size(); ++i) {
            if(controls[i] == tempPtr) {
                return true;
            }
        }
    }
    return false;
}

void Panel::draw(Graphics& g, int x, int y, size_t z) {
    int relativeX, relativeY;
    Control::draw(g, x, y, z);
    for(int i = 0; i < controls.size(); ++i) {
        relativeX = controls[i]->getLeft();
        relativeY = controls[i]->getTop();
        g.setForeground(controls[i]->getTextColor());
        g.setBackground(controls[i]->getBackgroundColor());
        controls[i]->draw(g, x + relativeX, y + relativeY, z);
    }
}

void Panel::mousePressed(int x, int y, bool isLeft) {
    if(focusInPanel()) {
        getFocus()->mousePressed(x, y, isLeft);
    }
}

void Panel::keyDown(int keyCode, char charecter) {
    if(focusInPanel()) {
        getFocus()->keyDown(keyCode, charecter);
    }
}

void Panel::getAllControls(vector<Control*>* controls) {
    for(int i = 0; i < this->controls.size(); ++i) {
        controls->push_back(this->controls[i]);
        this->controls[i]->getAllControls(controls);
    }
}
