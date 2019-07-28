#include "CheckList.h"

CheckList::CheckList(short left, short top, short width, Border* border, Color textColor, Color backgroundColor) :
    Control(left, top, width, 0, border, textColor, backgroundColor) {
        focusIndex = -1;
}

CheckList::~CheckList() {
    for(int i = 0; i < items.size(); ++i) {
        delete items[i];
    }
}

void CheckList::addToList(string item) {
    ListItem* newItem = new ListItem(0, (items.size() * 3), getWidth() - 3, textColor, backgroundColor, item);
    newItem->addListener(this);
    newItem->setSelectedString("[X] ");
    newItem->setUnselectedString("[ ] ");
    items.push_back(newItem);
    Control::setHeight(Control::getHeight() + 3);
}

bool CheckList::addSelectedItem(string item) {
    for(int i = 0; i < selectedItems.size(); ++i) {
        if(item.compare(selectedItems[i]) == 0) {
            return false;
        }
    }
    selectedItems.push_back(item);
    return true;
}

bool CheckList::removeSelectedItem(string item) {
    for(int i = 0; i < selectedItems.size(); ++i) {
        if(item.compare(selectedItems[i]) == 0) {
            selectedItems.erase(selectedItems.begin() + i);
            return true;
        }
    }
    return false;
}

void CheckList::getSelectedItems(vector<string>& selected) {
    for(int i = 0; i < selectedItems.size(); ++i) {
        selected.push_back(selectedItems[i]);
    }
}

void CheckList::invertColors(ListItem* item){
    Color tempColor = item->getTextColor();
    item->setTextColor(item->getBackgroundColor());
    item->setBackgroundColor(tempColor);
}

void CheckList::draw(Graphics& g, int x, int y, size_t z) {
    int relativeX, relativeY;
    if(z == 0) {
        Control::draw(g, x, y, z);
        if(getFocusIndex() == -1 && getFocus() == this) {
            focusIndex = 0;
            setFocus(*items[0]);
        }
        for(int i = 0; i < items.size(); ++i) {
            relativeX = items[i]->getLeft();
            relativeY = items[i]->getTop();
            if(focusIndex == i) {
                invertColors(items[i]);
                items[i]->draw(g, x + relativeX + 1, y + relativeY + 1, z);
                invertColors(items[i]);
            }
            else {
                items[i]->draw(g, x + relativeX + 1, y + relativeY + 1, z);
            }
        }
    }
}

void CheckList::mousePressed(int x, int y, bool isLeft) {
    int l = getLeft(), t = getTop(), w = getWidth(), h = getHeight();
    if(x >= l && x <= l + w && y >= t && y <= t + h && isLeft) {
        if(getMessageBoxLock() == false) {
            for(int i = 0; i < items.size(); ++i) {
                items[i]->mousePressed(x - l - 1, y - t - 1, isLeft);
            }
        }
    }}

void CheckList::keyDown(int keyCode, char charecter) {
    if(getFocusIndex() != -1) {
        if(keyCode == VK_RETURN || keyCode == VK_SPACE) {
            if(items[focusIndex]->getSelected() == true) {
                items[focusIndex]->setSelected(false);
                removeSelectedItem(items[focusIndex]->getValue());
            }
            else {
                items[focusIndex]->setSelected(true);
                addSelectedItem(items[focusIndex]->getValue());
            }
            return;
        }
        if(keyCode == VK_UP || keyCode == VK_NUMPAD8){
            if(focusIndex == 0) {
                focusIndex = items.size() - 1;
            }
            else {
                --focusIndex;
            }
            Control::setFocus(*items[focusIndex]);
            return;
        }
        if(keyCode == VK_DOWN || keyCode == VK_NUMPAD2){
            if(focusIndex == items.size() - 1) {
                focusIndex = 0;
            }
            else {
                ++focusIndex;
            }
            Control::setFocus(*items[focusIndex]);
            return;
        }
    }
}

void CheckList::getAllControls(vector<Control*>* controls) {
    for(int i = 0; i < items.size(); ++i) {
        controls->push_back(items[i]);
    }
}

int CheckList::getFocusIndex() {
    Control* tempPtr = getFocus();
    for(int i = 0; i < items.size(); ++i) {
        if(items[i] == tempPtr) {
            focusIndex = i;
            return i;
        }
    }
    focusIndex = -1;
    return -1;
}

void CheckList::update(int x, int y, string s) {
    for(int i = 0; i < items.size(); ++i) {
        if(s.compare(items[i]->getValue()) == 0) {
            if(items[i]->getSelected() == true) {
                items[i]->setSelected(false);
                removeSelectedItem(items[i]->getValue());
            }
            else {
                items[i]->setSelected(true);
                addSelectedItem(items[i]->getValue());
            }
            focusIndex = i;
            Control::setFocus(*items[i]);
            return;
        }
    }
}
