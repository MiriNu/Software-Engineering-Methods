#include "textbox.h"
#include "../Common/Graphics.h"
#include "../Common/Border/SingleBorder.h"
#include <iostream>
#include <stdlib.h>


TextBox::TextBox(short width, short top, short left) : Label(left, top, width, 1, new SingleBorder(), Color::White, Color::Black, ""){
        currentCoord = {left + 1 + value.length(), top + 1};
        oldWidth = width;
        setFocus(*this);
}

void TextBox:: mousePressed(int x, int y, bool isLeft){
    if(isLeft){
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        currentCoord = { x, y };
        SetConsoleCursorPosition(handle, currentCoord);
    }
}

void TextBox:: keyDown(int keyCode, char character){
    int textWidth = value.length();
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if((keyCode >= 0x30  && keyCode <= 122) || keyCode == VK_SPACE){
        size_t offset = currentCoord.X - this->left;
        string s;
        s += character;
        currentCoord = { currentCoord.X + 1, currentCoord.Y };
        value.insert(offset - 1, &character);
        if(value.length() >= width)
            width += 2;
        }

    if(keyCode == VK_LEFT || keyCode == VK_RIGHT){
        auto offset = currentCoord.X - this->left;
        if(offset - 1 > 0 && keyCode == VK_LEFT){
            currentCoord = { currentCoord.X - 1, currentCoord.Y };
            SetConsoleCursorPosition(handle, currentCoord);
        }

        if(offset - 1 < textWidth && keyCode == VK_RIGHT){
            currentCoord = { currentCoord.X + 1, currentCoord.Y };
            SetConsoleCursorPosition(handle, currentCoord);
        }
    }

    if(textWidth > 0 && (keyCode == VK_BACK || keyCode == VK_DELETE)){
        size_t offset = currentCoord.X - this->left;
        if(keyCode == VK_DELETE && offset - 1 < this->value.length()){
            this->value.erase(this->value.begin() + offset - 1);
        }
        if(keyCode == VK_BACK && this->value.length() > 0){
            if(offset - 1 > 0){
                this->value.erase(this->value.begin() + offset - 2);
                currentCoord = { currentCoord.X - 1, currentCoord.Y };
            }
        }
        if(this->value.length() < width){
            oldWidth = width;
            width - 2 > 12 ? width -= 1 : 12;
        }
    }
}

void TextBox::draw(Graphics& g, int x, int y, size_t z){
    g.setCursorVisibility(true);
    Label::draw(g, x, y, z);

    g.moveTo(currentCoord.X, currentCoord.Y);
}
