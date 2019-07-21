#include "Panel.h"

Panel::Panel() : Control() {}

Panel::Panel(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    Control(left, top, width, height, border, textColor, backgroundColor) {}

Panel::~Panel() {}

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

int Panel::getFocusIndex() {
    Control* tempPtr = getFocus();
    for(int i = 0; i < controls.size(); ++i) {
        if(controls[i] == tempPtr) {
            focusIndex = i;
            return i;
        }
        else if(controls[i]->getFocusIndex() != -1) {
            focusIndex = i;
            return i;
        }
    }
    focusIndex = -1;
    return -1;
}

void Panel::draw(Graphics& g, int x, int y, size_t z) {
    int relativeX, relativeY;
    if(z == 0) {
        Control::draw(g, x, y, z);
        for(int i = 0; i < controls.size(); ++i) {
            relativeX = controls[i]->getLeft();
            relativeY = controls[i]->getTop();
            g.setForeground(controls[i]->getTextColor());
            g.setBackground(controls[i]->getBackgroundColor());
            controls[i]->draw(g, x + relativeX + 1, y + relativeY + 1, z);
        }
    }
}

void Panel::mousePressed(int x, int y, bool isLeft) {
    if(getFocusIndex() != -1) {
        controls[focusIndex]->mousePressed(x - getLeft(), y - getTop(), isLeft);
    }
}

void Panel::keyDown(int keyCode, char charecter) {
    if(getFocusIndex() != -1) {
        controls[focusIndex]->keyDown(keyCode, charecter);
    }
}

void Panel::getAllControls(vector<Control*>* controls) {
    for(int i = 0; i < this->controls.size(); ++i) {
        controls->push_back(this->controls[i]);
        this->controls[i]->getAllControls(controls);
    }
}
