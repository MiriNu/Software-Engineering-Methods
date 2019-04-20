#include<iostream>  
#include <windows.h>
#include "checklist.h"
 
//Get selected checkboxes positions from checklist 
std::string getSelectedItems(CheckList cl);
//Remove given row
bool deleteRow(HANDLE hNewScreenBuffer, COORD coord, std::string selectedItems);

int main() 
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
		fprintf(stderr,"Error: CreateConsoleScreenBuffer failed.\n");
	}
    if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
	{
		fprintf(stderr,"Error: SetConsoleActiveScreenBuffer failed.\n");
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

    CheckList cl(50,6);     
    cl.addCheckBox("Lorem of house Ipsum");  
    cl.addCheckBox("AM I GOING TO BE THE CHOSEN ONE");  
	cl.addCheckBox("meep");
	cl.addCheckBox("Two types of Starks will die during April-May.");  
	cl.addCheckBox("^\\_('v')_/^");  
	cl.deleteCheckBox(2);
	cl.setCoord(5,2);
    cl.draw(hNewScreenBuffer);  

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
		}

		std::string selectedItems = "Currently selected: "+ getSelectedItems(cl);
		DWORD written;
		COORD coord = { cl.getX() , (SHORT)(cl.getCLheight() + 2)};

		//Delete previous output
		if (!deleteRow(hNewScreenBuffer, coord, selectedItems))
		{
			return 1;
		}
		//Write currently selected checkboxes
		if (!SetConsoleCursorPosition(hNewScreenBuffer, coord))
		{
			return 1;
		}
		if (!WriteConsole(hNewScreenBuffer, selectedItems.c_str(), selectedItems.size(), &written,NULL))
		{
			return 1;
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

//Remove given row
bool deleteRow(HANDLE hNewScreenBuffer, COORD coord, std::string selectedItems)
{
	DWORD written;

	if (!SetConsoleCursorPosition(hNewScreenBuffer, coord))
	{
		return false;
	}
	std::string delrow = " ";
	for (int i = 0; i < selectedItems.length(); i++)
	{
		delrow += "  ";
	}

	//Delete previous output
	if (!WriteConsole(hNewScreenBuffer, delrow.c_str(), delrow.size(), &written, NULL))
	{
		return false;
	}

	if (!SetConsoleCursorPosition(hNewScreenBuffer, coord))
	{
		return false;
	}
	return true;
}