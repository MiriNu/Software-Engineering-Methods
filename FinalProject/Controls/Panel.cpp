#include "Panel.h"

Panel::Panel(short left, short top, Border* border, Color textColor, Color backgroundColor) :
    Control(left, top, 1, 1, border, textColor, backgroundColor) {
        calculateWidthAndHeight();
}

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
    calculateWidthAndHeight();
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
    if(z == 1) {
        Control* focusPtr = getFocus();
        relativeX = focusPtr->getLeft();
        relativeY = focusPtr->getTop();
        g.setForeground(focusPtr->getTextColor());
        g.setBackground(focusPtr->getBackgroundColor());
        focusPtr->draw(g, x + relativeX + 1, y + relativeY + 1, z);
    }
}

void Panel::mousePressed(int x, int y, bool isLeft) {
    int l = getLeft(), t = getTop(), w = getWidth(), h = getHeight();
    if(x >= l && x <= l + w && y >= t && y <= t + h && isLeft) {
        if(getMessageBoxLock() == false) {
            for(int i = 0; i < controls.size(); ++i) {
                controls[i]->mousePressed(x - l - 1, y - t - 1, isLeft);
            }
        }
        else if(getFocusIndex() != -1) {
            controls[focusIndex]->mousePressed(x - l - 1, y - t - 1, isLeft);
        }
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

void Panel::calculateWidthAndHeight() {
    short calcWidth = 0, calcHeight = 0, ciLeft, ciTop, ciWidth, ciHeight;
    for(int i = 0; i < controls.size(); ++i) {
        ciLeft = controls[i]->getLeft();
        ciTop = controls[i]->getTop();
        ciWidth = controls[i]->getWidth();
        ciHeight = controls[i]->getHeight();
        if(ciLeft + ciWidth > calcWidth) {
            calcWidth = ciLeft + ciWidth;
        }
        if(ciTop + ciHeight > calcHeight) {
            calcHeight = ciTop + ciHeight;
        }
    }
    setWidth(calcWidth + 2);
    setHeight(calcHeight + 2);
}
