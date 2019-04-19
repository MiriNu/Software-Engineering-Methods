#include<iostream>  
#include <windows.h>
#include "checklist.h"
  

int main(void) 
{ 
    HANDLE hNewScreenBuffer;
    hNewScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hNewScreenBuffer);
    CheckList cl(0,0);     
    cl.addCheckBox("string");  
    cl.addCheckBox("streng");  
    cl.draw(hNewScreenBuffer);  
    MessageBoxA(NULL,"oii","wat",0);
    return 0; 
} 