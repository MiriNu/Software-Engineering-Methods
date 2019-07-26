#include "EntryBox.h"
#include <iostream>
//#include <string>

EntryBox::EntryBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor, std::string value):
Control(left, top, width, 4, border, textColor, backgroundColor),
selector(Button(left, top, 5, border, textColor, backgroundColor, "[ ] ")), 
value(Label(left + 5,top,width,border,textColor,backgroundColor,value)),
isSelected(false), 
isFocused(false)
{selector.addListener(this);};

void EntryBox::draw(Graphics& g, int x, int y, size_t z)
{
    if(z == 0)
    {
        //Control::draw(g, x, y, z);
        selector.draw(g, selector.getLeft(), selector.getTop(), z);
        value.draw(g, value.getLeft(), value.getTop(), z);
    }
}

void EntryBox::mousePressed(int x, int y, bool isLeft) {
    selector.mousePressed(x, y, isLeft);
}

void EntryBox::update(int x, int y, string s)
{
    setFocused(true);   
    setSelected(!getSelected());
}

 void EntryBox::invertColor(Control* ctrl)
 {
    Color prevTextColor = ctrl->getTextColor();
    ctrl->setTextColor(ctrl->getBackgroundColor());
    ctrl->setBackgroundColor(prevTextColor);
 }

//Getters
bool         EntryBox::getSelected()  { return isSelected; }
bool         EntryBox::getFocused()   { return isFocused; }
std::string  EntryBox::getValue()     { return value.getValue(); }
        
//Setters
void EntryBox::setSelected(const bool selected) 
{ 
    isSelected = selected; 
    if (isSelected)
    {
        selector.setValue("[X] ");
    }
    else
    {
        selector.setValue("[ ] ");
    }
} 
void EntryBox::setFocused(const bool focused)   
{   
    isFocused = focused; 
    invertColor(&selector);
    invertColor(&value);
}