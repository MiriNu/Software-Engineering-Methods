#include "NumericBox.h"

NumericBox::NumericBox(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    Control(left, top, width + 1, height + 1, new SingleBorder(), textColor, backgroundColor),
    value(left + 7, top + 1, 1, 1, new SingleBorder(), textColor, backgroundColor, "0"),
    add(left + 2, top + 1, 1, 1, new SingleBorder(), textColor, backgroundColor, " +"),
    subtract(left + 12, top + 1, 1, 1, new SingleBorder(), textColor, backgroundColor, " -")
{
    add.addListener(this);
    subtract.addListener(this);
}


void NumericBox::update(int x, int y){
    int addL = add.getLeft(), addT = add.getTop(), addW = add.getWidth(), addH = add.getHeight();
    int subL = subtract.getLeft(), subT = subtract.getTop(), subW = subtract.getWidth(), subH = subtract.getHeight();

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
    int numericVal = atoi(value.getValue().c_str());
    ++numericVal;
    value.setValue(to_string(numericVal));
}

void NumericBox::subFromVal(){
    int numericVal = atoi(value.getValue().c_str());
    --numericVal;
    value.setValue(to_string(numericVal));
}

void NumericBox::mousePressed(int x, int y, bool isLeft) {
    add.mousePressed(x, y, isLeft);
    subtract.mousePressed(x, y, isLeft);
}

void NumericBox::draw(Graphics& g, int x, int y, size_t z){
    short relativeX, relativeY;
    if(z == 0){
    Control::draw(g, x, y, z);

    relativeX = value.getLeft();
    relativeY = value.getTop();
    value.draw(g, relativeX, relativeY, z);

    relativeX = add.getLeft();
    relativeY = add.getTop();
    add.draw(g, relativeX, relativeY, z);

    relativeX = subtract.getLeft();
    relativeY = subtract.getTop();
    subtract.draw(g, relativeX, relativeY, z);
    }
}