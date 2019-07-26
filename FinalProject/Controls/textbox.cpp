#include "TextBox.h"


TextBox::TextBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor) : Label(left, top, width, border, textColor, backgroundColor, ""){
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        currentCoord = {left + 1 + value.length(), top + 1};
        SetConsoleCursorPosition(handle, currentCoord);
}

void TextBox:: mousePressed(int x, int y, bool isLeft){
    int l = getLeft() + 1, t = getTop() + 1, w = getWidth(), h = getHeight();
    if(x >= l && x <= l + w &&  y >= t && y <= t + h && isLeft) {
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if(x > value.length() + l)
            x = value.length() + l;
        else if(x == value.length() + l && value.length() != 0)
            x = value.length() + l - 1;

        currentCoord = { x, top + 1 };
        SetConsoleCursorPosition(handle, currentCoord);
    }
    return;
}

void TextBox::setText(string text){ 
    if(text.length() <= width)
        value = text;
    return; 
}


void TextBox:: keyDown(int keyCode, char character){
    int textWidth = value.length();
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if((keyCode >= 0x30  && keyCode <= 122) || keyCode == VK_SPACE){
        if(textWidth >= width)
            return;
        size_t offset = currentCoord.X - this->left;
        string s;
        s += character;
        currentCoord = { currentCoord.X + 1, currentCoord.Y };
        value.insert(offset - 1, &character);
        return;
    }

    if(keyCode == VK_LEFT || keyCode == VK_RIGHT){
        auto offset = currentCoord.X - this->left;
        if(offset - 1 > 0 && keyCode == VK_LEFT){
            currentCoord = { currentCoord.X - 1, currentCoord.Y };
            SetConsoleCursorPosition(handle, currentCoord);
            return;
        }

        if(offset - 1 < textWidth && keyCode == VK_RIGHT){
            currentCoord = { currentCoord.X + 1, currentCoord.Y };
            SetConsoleCursorPosition(handle, currentCoord);
            return;
        }
    }

    if(textWidth > 0 && (keyCode == VK_BACK || keyCode == VK_DELETE)){
        size_t offset = currentCoord.X - this->left;
        if(keyCode == VK_DELETE && offset - 1 < this->value.length()){
            this->value.erase(this->value.begin() + offset - 1);
            return;
        }
        if(keyCode == VK_BACK && this->value.length() > 0){
            if(offset - 1 > 0){
                this->value.erase(this->value.begin() + offset - 2);
                currentCoord = { currentCoord.X - 1, currentCoord.Y };
            }
        }
    }
}

void TextBox::draw(Graphics& g, int x, int y, size_t z){
    Label::draw(g, x + 1, y + 1, z);
    
    g.moveTo(currentCoord.X + 2, currentCoord.Y + 2);
    g.setCursorVisibility(true);
}
