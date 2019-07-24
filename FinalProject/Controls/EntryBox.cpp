#include "EntryBox.h"
#include <iostream>

EntryBox::EntryBox(string v) 
{
    this.value = new Label(v);
};

bool EntryBox::getSelected() const
{
    return this.isSelected;
}