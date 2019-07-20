#include "textbox.h"
#include "Graphics.h"
#include "Border/SingleBorder.h"
#include <iostream>
#include <stdlib.h>


TextBox::TextBox(short width, short top, short left) : Control(left, top, width, 1, new SingleBorder(), Color::White, Color::Black), value(""){
        currentCoord = {left + 1 + value.length(), top + 1};
        oldWidth = width;
}

void TextBox:: handleMouseEvent(MOUSE_EVENT_RECORD& event){

    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        currentCoord = event.dwMousePosition;
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
    Control::draw();
    for(int i = width; i < oldWidth; ++i)
        std::cout << " ";

    SetConsoleCursorPosition(handle,{ coord.X, coord.Y + 1 });

    for(int i = 0; i < value.length(); ++i)
        std::cout << value[i];
    
    for(int i = value.length(); i < width; ++i)
        std::cout << " ";
    
    for(int i = width; i < oldWidth + 1; ++i)
        std::cout << " ";

    SetConsoleCursorPosition(handle,{ left, top + 2 });

    for(int i = width; i < oldWidth; ++i)
        std::cout << " ";

    SetConsoleCursorPosition(handle, currentCoord);
}