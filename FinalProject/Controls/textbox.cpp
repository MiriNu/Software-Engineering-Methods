#include "TextBox.h"


TextBox::TextBox(short width, short top, short left) : Label(left, top, width, new SingleBorder(), Color::White, Color::Black, ""){
        currentCoord = {left + 1 + value.length(), top + 1};
}

void TextBox:: mousePressed(int x, int y, bool isLeft){
    int l = getLeft(), t = getTop(), w = value.length(), h = 1;
    if(x >= l && x <= l + w &&  y >= t && y <= t + h && isLeft) {
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        currentCoord = { x, y };
        SetConsoleCursorPosition(handle, currentCoord);
    }

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
    }
}

void TextBox::draw(Graphics& g, int x, int y, size_t z){
    Label::draw(g, x + 1, y + 1, z);
    
    g.moveTo(currentCoord.X + 2, currentCoord.Y + 2);
    g.setCursorVisibility(true);
}
