#include<iostream>  
#include <windows.h>
#include "checklist.h"
 
//Get selected checkboxes positions from checklist 
std::string getSelectedItems(CheckList cl);
//Remove given row
void deleteRow(HANDLE hNewScreenBuffer, COORD coord, std::string selectedItems);

int main(void) 
{ 

	//Create a new screen 
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hNewScreenBuffer;
    hNewScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hNewScreenBuffer);

	//Cursors are ugly, let's get rid of them. 
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hNewScreenBuffer, &cursorInfo);

	//Sanity check
	if (! SetConsoleMode(hStdin, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_INSERT_MODE) ) 
		return 1;

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

		ReadConsoleInput(hStdin, &ir, 1, &count);

		if (count)
		{
			if (ir.EventType == KEY_EVENT)
			{
				cl.handleKeyboardEvent(ir.Event.KeyEvent, hNewScreenBuffer);
			}

			if (ir.EventType == MOUSE_EVENT)
			{
				cl.handleMouseEvent(ir.Event.MouseEvent, hNewScreenBuffer);
			}
		}

		std::string selectedItems = "Currently selected: "+ getSelectedItems(cl);
		DWORD written;
		COORD coord = { cl.getX() , cl.getCLheight() + 2 };
		//Delete previous output
		deleteRow(hNewScreenBuffer, coord, selectedItems);
		//Write currently selected checkboxes
		SetConsoleCursorPosition(hNewScreenBuffer, coord);
		WriteConsole(hNewScreenBuffer, selectedItems.c_str(), selectedItems.size(), &written,NULL);
	}

    //MessageBoxA(NULL,"oii","wat",0);
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
void deleteRow(HANDLE hNewScreenBuffer, COORD coord, std::string selectedItems)
{
	DWORD written;

	SetConsoleCursorPosition(hNewScreenBuffer, coord);
	std::string delrow = " ";
	for (int i = 0; i < selectedItems.length(); i++)
	{
		delrow += "  ";
	}

	//Delete previous output
	WriteConsole(hNewScreenBuffer, delrow.c_str(), delrow.size(), &written, NULL);
	SetConsoleCursorPosition(hNewScreenBuffer, coord);
}