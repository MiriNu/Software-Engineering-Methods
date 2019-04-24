#include "textbox.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

TextBox::TextBox(short width, short top, short left) : 
    width(width), top(top), left(left), hasBorder(true), value(""), 
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY){
        currentCoord = {left + 1 + value.length(), top + 1};
        oldWidth = width;
    }

void TextBox:: handleMouseEvent(MOUSE_EVENT_RECORD& event){
    std::ofstream tmp;
    tmp.open("test.txt");
    tmp << "here";
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        currentCoord = event.dwMousePosition;
        tmp << "here2";
        SetConsoleCursorPosition(handle, currentCoord);
    }
}

void TextBox:: handleKeyboardEvent(KEY_EVENT_RECORD& event){
    int textWidth = value.length();
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!event.bKeyDown)
        return;
    
    if((event.wVirtualKeyCode >= 0x30 && event.wRepeatCount <= 0x5a) || event.wVirtualKeyCode == VK_SPACE) {
        size_t offset = currentCoord.X - this->left;
        currentCoord = { currentCoord.X + 1, currentCoord.Y };
        this->value.insert(offset - 1, &event.uChar.AsciiChar);
        if(this->value.length() >= width)
            width += 2;
    
        this->draw();
    }

    if(event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT){
        auto offset = currentCoord.X - this->left;
        if(offset - 1 > 0 && event.wVirtualKeyCode == VK_LEFT){
            currentCoord = { currentCoord.X - 1, currentCoord.Y };
            SetConsoleCursorPosition(handle, currentCoord);
        }

        if(offset - 1 < textWidth && event.wVirtualKeyCode == VK_RIGHT){
            currentCoord = { currentCoord.X + 1, currentCoord.Y };
            SetConsoleCursorPosition(handle, currentCoord);
        }
    }

    if(textWidth > 0 && (event.wVirtualKeyCode == VK_BACK || event.wVirtualKeyCode == VK_DELETE)){
        size_t offset = currentCoord.X - this->left;
        if(event.wVirtualKeyCode == VK_DELETE && offset - 1 < this->value.length()){
            this->value.erase(this->value.begin() + offset - 1);
        }
        if(event.wVirtualKeyCode == VK_BACK && this->value.length() > 0){
            if(offset - 1 > 0){
                this->value.erase(this->value.begin() + offset - 2);
                currentCoord = { currentCoord.X - 1, currentCoord.Y };
            }
        }
        if(this->value.length() < width){
            oldWidth = width;
            width - 2 > 12 ? width -= 1 : 12;
        }
        
        this->draw();
    }
}

void TextBox::draw(){
    COORD coord =  {left, top};
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color | (background << 4));

    std::cout << (char)0xda;
    for(int i = 0; i < width; ++i)
        std::cout << (char)0xc4;    

    std::cout << (char)0xbf;

    for(int i = width; i < oldWidth; ++i)
        std::cout << " ";

    SetConsoleCursorPosition(handle,{ coord.X, coord.Y + 1 });
    std::cout << (char)0xb3;

    for(int i = 0; i < value.length(); ++i)
        std::cout << value[i];
    
    for(int i = value.length(); i < width; ++i)
        std::cout << " ";
    
    for(int i = width; i < oldWidth + 1; ++i)
        std::cout << " ";

    SetConsoleCursorPosition(handle,{ left + width + 1, top + 1 });
    std::cout << (char)0xb3;


    SetConsoleCursorPosition(handle,{ left, top + 2 });
    std::cout << (char)0xc0;

    for(int i = 0; i < width; ++i)
        std::cout << (char)0xc4;  

    std::cout << (char)0xd9;
        
    for(int i = width; i < oldWidth; ++i)
        std::cout << " ";

    SetConsoleCursorPosition(handle, currentCoord);
}