#include "ListItem.h"
#include "../Common/Border/NullBorder.h"

ListItem::ListItem(short left, short top, short width, Color textColor, Color backgroundColor, string value) :
    Button(left, top, width, new NullBorder, textColor, backgroundColor, value) {
        selected = false;
        selectedString = "";
        unselectedString = "";
}

ListItem::~ListItem() {
    delete this->getBorder();
}

void ListItem::draw(Graphics& g, int x, int y, size_t z) {
    if(z == 0) {
        Button::draw(g, x, y, z);
        if(selected == true) {
            g.write(x + 1, y + 1, selectedString);
        }
        else {
            g.write(x + 1, y + 1, unselectedString);
        }
        g.write(x + 5, y + 1, getValue());
    }
}

void ListItem::mousePressed(int x, int y, bool isLeft) {
    Button::mousePressed(x, y, isLeft);
}

void ListItem::keyDown(int keyCode, char charecter) {
    dynamic_cast<Control*>(listeners[0])->keyDown(keyCode, charecter);
}
