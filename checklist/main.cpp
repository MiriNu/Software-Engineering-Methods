#include<iostream>  
#include <windows.h>
#include "checklist.h"
 
//Get selected checkboxes positions from checklist 
std::string getSelectedItems(CheckList cl);
//Refresh selected items
bool showSelected(HANDLE hNewScreenBuffer, CheckList cl);

int main(void) 
{ 

	//Create a new screen 
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
	{
		return 1;
	}
    HANDLE hNewScreenBuffer;
    hNewScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (hNewScreenBuffer == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Error: CreateConsoleScreenBuffer failed.\n";
	}
    if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
	{
		std::cerr << stderr,"Error: SetConsoleActiveScreenBuffer failed.\n";
	}

	//Cursors are ugly, let's get rid of them. 
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	if (!SetConsoleCursorInfo(hNewScreenBuffer, &cursorInfo))
	{
		return 1;
	}

	//Sanity check
	if (! SetConsoleMode(hStdin, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_INSERT_MODE) )
	{
		return 1;
	}

    CheckList cl(50, 6);
    cl.addCheckBox("Lorem of house Ipsum");  
    cl.addCheckBox("AM I GOING TO BE THE CHOSEN ONE");  
	cl.addCheckBox("meep");
	cl.addCheckBox("Two types of Starks will die during April-May.");  
	cl.addCheckBox("^\\_('v')_/^");  
	if (!cl.draw(hNewScreenBuffer))
	{
		return 1;
	}
	if (!cl.deleteCheckBox(2, hNewScreenBuffer))
	{
		return 1;
	}
	if (!cl.draw(hNewScreenBuffer))
	{
		return 1;
	}
	if(!cl.setCoord(5, 2, hNewScreenBuffer))
	{
		return 1;
	}
	if (!cl.draw(hNewScreenBuffer))
	{
		return 1;
	}

	while (1)
	{
		INPUT_RECORD ir;
		DWORD count;

		if (!ReadConsoleInput(hStdin, &ir, 1, &count))
		{
			return 1;
		}

		if (count)
		{
			if (ir.EventType == KEY_EVENT)
			{
				if (!cl.handleKeyboardEvent(ir.Event.KeyEvent, hNewScreenBuffer))
				{
					return 1;
				}
			}

			if (ir.EventType == MOUSE_EVENT)
			{
				if (!cl.handleMouseEvent(ir.Event.MouseEvent, hNewScreenBuffer))
				{
					return 1;
				}
			}

			if (ir.Event.MouseEvent.dwEventFlags != MOUSE_MOVED && !showSelected(hNewScreenBuffer, cl))
			{
				return 1;
			}
		}

	}

    return 0; 
} 

//Get selected checkboxes positions from checklist 
std::string getSelectedItems(CheckList cl)
{
	std::vector<int> cbs = cl.getSelectedPos();
	std::string nums =" ";

	for (int i = 0; i < cbs.size(); i++)
	{
		nums += std::to_string(cbs[i])+" ";
	}

 	return nums +"\n";
}

//Refresh selected items
bool showSelected(HANDLE hNewScreenBuffer, CheckList cl)
{
	std::string selectedItems = "Currently selected: " + getSelectedItems(cl);
	DWORD written;
	COORD coord = { cl.getX() , cl.getY() + (SHORT)(cl.getCLheight()) };

	//Delete previous output
	if (!FillConsoleOutputCharacter(hNewScreenBuffer, ' ', selectedItems.length(), coord, &written))
	{
		return false;
	}
	//Write currently selected checkboxes
	if (!SetConsoleCursorPosition(hNewScreenBuffer, coord))
	{
		return 1;
	}
	if (!WriteConsole(hNewScreenBuffer, selectedItems.c_str(), selectedItems.size(), &written, NULL))
	{
		return 1;
	}
}