#include<iostream>  
#include <windows.h>
#include "checklist.h"
  
//Constructor
CheckList::CheckList( SHORT x, SHORT y) : x(x), y(y) { }

//Getters
SHORT CheckList::getX() const { return x; }
SHORT CheckList::getY() const { return y; }
//Only one cb should be focused at each time, this function provides the pos of said cb
int   CheckList::getFocusedPos() const
{
    for (int i=0; i<cb.size(); i++)
    {
        if(cb[i].getFocused())
        {
            return i;
        }
    }
    return -1; 
}

//Get a vector of selected attributes
std::vector<int> CheckList::getSelectedPos() const
{
	std::vector<int> selectedCB;
	for (int i = 0; i < cb.size(); i++)
	{
		if (cb[i].getSelected())
		{
			selectedCB.push_back(i);
		}
	}
	return selectedCB;
}

//Get the width of the cl according to the longest cb value
int	  CheckList::getCLWidth() const
{
	int maxLen = 0;
	for (int i = 0; i < cb.size(); i++)
	{
		if (cb[i].getValue().length() > maxLen)
		{
			maxLen = cb[i].getValue().length();
		}
	}

	return maxLen+1;
}

//Get the height of the cl according to the size of cb
int CheckList::getCLheight() const { return cb.size()+1; }

//Setters
void CheckList::setCoord(const SHORT xPos, const SHORT yPos)
{ 
	x = xPos; 
	y = yPos;
	for (int i = 0; i < cb.size(); i++)
	{
		cb[i].setX(xPos);
		cb[i].setY(yPos + i);
	}
}

//Keyboard event handler
void CheckList::handleKeyboardEvent(KEY_EVENT_RECORD& event, HANDLE hCSB)
{
	DWORD focusedCB = getFocusedPos();
    if (!event.bKeyDown) return;
    
    switch(event.wVirtualKeyCode)
    {
        //Pressed arrow down
        case VK_DOWN:
            if (focusedCB != -1 && focusedCB+1<cb.size())
            {
                cb[focusedCB].setFocused(false);
                cb[focusedCB+1].setFocused(true);
            }
            else
            {
                cb[0].setFocused(true);
				cb[cb.size()-1].setFocused(false);
            }
            break;

        //Pressed arrow up    
        case VK_UP:
			if (focusedCB != -1 && focusedCB != 0)
			{
				cb[focusedCB].setFocused(false);
				cb[focusedCB - 1].setFocused(true);
			}
			else
			{
				cb[cb.size()-1].setFocused(true);
				cb[0].setFocused(false);
			}
            break;

        //Pressed spacebar    
        case VK_SPACE:
			cb[focusedCB].setSelected(!cb[focusedCB].getSelected());
            break;

        default:
            break;
            
    }
    draw(hCSB);  
}

//Mouse event handler
void CheckList::handleMouseEvent(MOUSE_EVENT_RECORD& event, HANDLE hCSB)
{
	if (event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
	{
		int xRange = getCLWidth() + getX();
		int yRange = cb.size() + getY();
		COORD pos = event.dwMousePosition;

		//Check if click is in the range of checklist 
		if (pos.X <= xRange && pos.X>getX() && pos.Y<= yRange)
		{
			for (int i = 0; i < cb.size(); i++)
			{
				if (i + getY() != pos.Y)
				{
					cb[i].setFocused(false);
				}
				else
				{
					cb[i].setFocused(true);
					cb[i].setSelected(!cb[i].getSelected());
				}
			}
		}
		draw(hCSB);

	}
}

//Add checkbox to the list of checkboxes (checklist)
void CheckList::addCheckBox(const std::string value)
{
	DWORD size = cb.size();
	cb.push_back(CheckBox(x, y + size, value));

}

//Delete cb by position
void CheckList::deleteCheckBox(SHORT pos)
{
	if (pos >= 0 && pos < cb.size())
	{
		cb.erase(cb.begin()+pos);
	}

	for (int i = pos; i < cb.size(); i++)
	{
		cb[i].setY(cb[i].getY()-1);
	}
}

//Draw all existing checkboxes on a given screen
void CheckList::draw (HANDLE hCSB)
{
    for (int i=0; i<cb.size(); i++)
    {
        cb[i].draw(hCSB);
    }
}

