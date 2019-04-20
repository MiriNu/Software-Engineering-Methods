#include<iostream>  
#include <windows.h>
#include "checkbox.h"

//Constructor  
CheckBox::CheckBox(SHORT x, SHORT y, std::string value) : 
x(x), value("[ ] "+value), y(y), selected(false), focused(false),
color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY), background(0)  { }

//Getters
SHORT		CheckBox::getY() const			{ return y; }
SHORT		CheckBox::getX() const			{ return x; }
bool        CheckBox::getSelected() const   { return selected; }
bool        CheckBox::getFocused() const    { return focused; }
WORD        CheckBox::getColor() const      { return color; }
WORD        CheckBox::getBg() const         { return background; }
std::string CheckBox::getValue() const      { return value.substr(value.find("] ") + 1); }

//Setters
void CheckBox::setY(const SHORT yPos)			{ y = yPos; }
void CheckBox::setX(const SHORT xPos)			{ x = xPos; }
void CheckBox::setSelected(const bool slctd)	{ selected = slctd; }
void CheckBox::setFocused(const bool fcsd)		{ focused = fcsd; }
void CheckBox::setValue(const std::string val)	{ value = "[ ] " + val; }


void CheckBox::draw (HANDLE hCSB)
{
    DWORD written;

    WriteConsoleOutputCharacterA (hCSB,value.c_str(),value.size(),COORD{x,y},&written);
    if (focused)
    {
        FillConsoleOutputAttribute(hCSB,FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | COMMON_LVB_REVERSE_VIDEO,value.size(),COORD{x,y},&written);
    }
	else
	{
		FillConsoleOutputAttribute(hCSB, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY , value.size(), COORD{ x,y }, &written);
	}
    if (selected)
    {
        WriteConsoleOutputCharacterA (hCSB,"V",1,COORD{x+1,y},&written);
    }
    
}