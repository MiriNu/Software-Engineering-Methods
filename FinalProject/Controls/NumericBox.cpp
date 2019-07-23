#include "NumericBox.h"

NumericBox::NumericBox(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    Control(left, top, width + 1, height + 1, new SingleBorder(), textColor, backgroundColor),
    value(left + 7, top + 1, 1, 1, new SingleBorder(), textColor, backgroundColor, " 0"),
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
    string temp = value.getValue();
    string temp2 = " ";
    int numericVal = atoi(temp.c_str());
    ++numericVal;
    temp2.append(to_string(numericVal));
    value.setValue(temp2);
}

void NumericBox::subFromVal(){
    string temp = value.getValue();
    string temp2 = " ";
    int numericVal = atoi(temp.c_str());
    --numericVal;
    temp2.append(to_string(numericVal));
    value.setValue(temp2);
}

void NumericBox::mousePressed(int x, int y, bool isLeft) {
    add.mousePressed(x - 7, y - 6, isLeft);
    subtract.mousePressed(x - 7, y - 6, isLeft);
}

void NumericBox::draw(Graphics& g, int x, int y, size_t z){
    short relativeX, relativeY;
    // Control::draw(g, x, y, z);

    relativeX = value.getLeft();
    relativeY = value.getTop();
    value.draw(g, x + relativeX + 1, y + relativeY + 1, z);
    // value.draw(g, relativeX, relativeY, z);
    relativeX = add.getLeft();
    relativeY = add.getTop();
    add.draw(g, x + relativeX + 1, y + relativeY + 1, z);

    // add.draw(g, relativeX, relativeY, z);
    relativeX = subtract.getLeft();
    relativeY = subtract.getTop();
    // subtract.draw(g, relativeX, relativeY, z);
    subtract.draw(g, x + relativeX + 1, y + relativeY + 1, z);
}