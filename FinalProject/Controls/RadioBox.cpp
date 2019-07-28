#include "RadioBox.h"

RadioBox::RadioBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor) :
    CheckList(left, top, width, border, textColor, backgroundColor) {
        selectedIndex = -1;
}

RadioBox::~RadioBox() {}

void RadioBox::addToList(string item) {
    CheckList::addToList(item);
    items[items.size() - 1]->setSelectedString("(O) ");
    items[items.size() - 1]->setUnselectedString("( ) ");
}

bool RadioBox::setSelectedItem(int index) {
    if(index < 0 || index >= items.size()) {
        return false;
    }
    if(selectedIndex != -1) {
        items[selectedIndex]->setSelected(false);
    }
    items[index]->setSelected(true);
    selectedIndex = index;
    return true;
}

bool RadioBox::clearSelection() {
    if(selectedIndex != -1) {
        items[selectedIndex]->setSelected(false);
    }
    selectedIndex = -1;
    return true;
}

void RadioBox::keyDown(int keyCode, char charecter) {
    if(getFocusIndex() != -1) {
        if(keyCode == VK_RETURN || keyCode == VK_SPACE) {
            setSelectedItem(focusIndex);
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
    }}

void RadioBox::update(int x, int y, string s) {
    for(int i = 0; i < items.size(); ++i) {
        if(s.compare(items[i]->getValue()) == 0) {
            if(i != selectedIndex) {
                setSelectedItem(i);
            }
            focusIndex = i;
            Control::setFocus(*items[i]);
            return;
        }
    }
}
