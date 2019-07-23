#include "NumericBox.h"

NumericBox::NumericBox(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor, string Value) :
    Control(left, top, width, height, new SingleBorder(), textColor, backgroundColor),
    value(left + 10, top + 10, 1, 1, new SingleBorder(), textColor, backgroundColor, Value),
    add(left + 5, top + 10, 1, 1, new SingleBorder(), textColor, backgroundColor, "+"),
    subtract(left + 15, top + 10, 1, 1, new SingleBorder(), textColor, backgroundColor, "-")
{
    add.addListener(this);
    subtract.addListener(this);
}


void NumericBox::update(int x, int y){
    int addL = add.getLeft(), addT = add.getTop(), addW = add.getWidth(), addH = add.getHeight();
    int subL = add.getLeft(), subT = add.getTop(), subW = add.getWidth(), subH = add.getHeight();
    value.setValue("potato");
    if(x >= addL && x <= addL + addW && y >= addT && y <= addT + addH) {
        addToVal();
        return;
    }

    if(x >= subL && x <= subL + subW && y >= subT && y <= subT + subH) {
        subFromVal();
        return;
    }
    return;
}

void NumericBox::addToVal(){
    string temp = value.getValue();
    int numericVal = atoi(temp.c_str());
    ++numericVal;
    value.setValue(to_string(numericVal));
}

void NumericBox::subFromVal(){
    string temp = value.getValue();
    int numericVal = atoi(temp.c_str());
    --numericVal;
    value.setValue(to_string(numericVal));
}


void NumericBox::draw(Graphics& g, int x, int y, size_t z){
    short relativeX, relativeY;
    Control::draw(g, x, y, z);

    relativeX = value.getLeft();
    relativeY = value.getTop();
    value.draw(g, x + relativeX + 1, y + relativeY + 1, z);

    relativeX = add.getLeft();
    relativeY = add.getTop();
    add.draw(g, x + relativeX + 1, y + relativeY + 1, z);

    relativeX = subtract.getLeft();
    relativeY = subtract.getTop();
    subtract.draw(g, x + relativeX + 1, y + relativeY + 1, z);
}