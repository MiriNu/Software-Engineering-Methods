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

	return maxLen+3;
}

//Get the height of the cl according to the size of cb
int CheckList::getCLheight() const { return cb.size()+1; }

//Setters
bool CheckList::setCoord(const SHORT xPos, const SHORT yPos, HANDLE hCSB)
{ 
	if(!clear(hCSB))
	{
		return false;
	}
	x = xPos; 
	y = yPos;

	for (int i = 0; i < cb.size(); i++)
	{
		cb[i].setX(xPos);
		cb[i].setY(yPos + i);
	}
	return true;
}

//Keyboard event handler
bool CheckList::handleKeyboardEvent(KEY_EVENT_RECORD& event, HANDLE hCSB)
{
	DWORD focusedCB = getFocusedPos();
    if (!event.bKeyDown)
	{
		return true;
	}
    
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
    if (!draw(hCSB))
	{
		return false;
	}
	return true;
}

//Mouse event handler
bool CheckList::handleMouseEvent(MOUSE_EVENT_RECORD& event, HANDLE hCSB)
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
		if (!draw(hCSB))
		{
			return false;
		}
	}
	return true;
}

//Add checkbox to the list of checkboxes (checklist)
void CheckList::addCheckBox(const std::string value)
{
	DWORD size = cb.size();
	cb.push_back(CheckBox(x, y + size, value));

}

//Delete cb by position
bool CheckList::deleteCheckBox(SHORT pos, HANDLE hCSB)
{
	if (!clear(hCSB))
	{
		return false;
	}

	if (pos >= 0 && pos < cb.size())
	{
		cb.erase(cb.begin()+pos);
		for (int i = pos; i < cb.size(); i++)
		{
			cb[i].setY(cb[i].getY() - 1);
		}
		return true;
	}
	return false;

}

//Draw all existing checkboxes on a given screen
bool CheckList::draw (HANDLE hCSB)
{
    for (int i=0; i<cb.size(); i++)
    {
        if (!cb[i].draw(hCSB))
		{
			return false;
		}
    }
	return true;
}

//clear checklist
bool CheckList::clear(HANDLE hCSB)
{
	int height = getCLheight();
	COORD coordScreen = { x, y };
	DWORD dwConSize = getCLWidth();
	DWORD cCharsWritten;

	for (SHORT i = 0; i < height; i++)
	{
		coordScreen = { x, y+i };
		if (!FillConsoleOutputCharacter(hCSB,' ', dwConSize, coordScreen, &cCharsWritten))
		{
			return false;
		}
	}
	return true;
}
