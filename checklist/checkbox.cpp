#include<iostream>  
#include <windows.h>
#include "checkbox.h"
  
CheckBox::CheckBox(DWORD id, short x, short y, std::string value) : 
    x(x), value("  "+value), y(y), selected(false), focused(false),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    background(0)  { }

void CheckBox::draw (HANDLE hCSB)
{
    DWORD written;
    WriteConsoleOutputCharacterA (hCSB,value.c_str(),value.size(),COORD{x,y},&written);
}