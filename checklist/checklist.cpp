#include<iostream>  
#include <windows.h>
#include "checklist.h"
  

CheckList::CheckList( short x, short y) : x(x), y(y) { }

void CheckList::addCheckBox (const std::string value)
{
    DWORD id = cb.size();
    cb.push_back(CheckBox(id,x,y+id,value));

}

void CheckList::draw (HANDLE hCSB)
{
    for (int i=0; i<cb.size(); i++)
    {
        cb[i].draw(hCSB);
    }
}
