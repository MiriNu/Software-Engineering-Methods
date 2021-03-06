#include "ComboBox.h"
#include "../Common/Border/SingleBorder.h"

ComboBox::ComboBox(short left, short top, Border* border, Color textColor, Color backgroundColor):
    Control(left, top, 17, 4, border, textColor, backgroundColor),
    showButton(left + 15, top + 1, 1, new SingleBorder(), textColor, backgroundColor, " +"),
    text(left + 1, top + 1, 10, new SingleBorder(), textColor, backgroundColor, ""),
    show(false), curr(0)
{
    showButton.addListener(this);
}

void ComboBox::addToList(string toAdd){
    Button* newButton = new Button(left + 1, text.getTop() + ( (1 + list.size()) * 3), 10, new SingleBorder(), textColor, backgroundColor, toAdd);
    newButton->addListener(this);
    list.push_back(newButton);
    Control::setHeight(Control::getHeight() + 3);
}

void ComboBox::mousePressed(int x, int y, bool isLeft){
    showButton.mousePressed(x, y, isLeft);
    if(show){
        for(unsigned int i = 0; i < list.size(); ++i)
            list[i]->mousePressed(x, y, isLeft);
    }
}

void ComboBox::keyDown(int keyCode, char character){
    Color tempColor;
    if(show){
        if(keyCode == VK_RETURN || keyCode == VK_SPACE){
            text.setValue(list[curr]->getValue());
            show = false;
            showButton.setValue(" +");
            invertColor(list[curr]);
            curr = 0;
            return;
        }

        if(keyCode == VK_UP || keyCode == VK_NUMPAD8){
            if(curr == 0)
                return;
            
            invertColor(list[curr]);
            --curr;
            invertColor(list[curr]);
            return;
        }

        if(keyCode == VK_DOWN || keyCode == VK_NUMPAD2){
            if(curr + 1 == list.size())
                return;

            invertColor(list[curr]);
            ++curr;
            invertColor(list[curr]);
            return;
        }
    }
    return;
}

void ComboBox::update(int x, int y, string s){
    bool changed = false;

    if(s.compare(" +") == 0 || s.compare(" -") == 0){
        show = !show;
        changed = true;
    }

    else if(show){
        for(unsigned int i = 0; i < list.size(); ++i){
            if(s == list[i]->getValue()){
                text.setValue(list[i]->getValue());
                show = false;
                changed = true;
            }
        }
    }

    if(changed){
        show ? showButton.setValue(" -") : showButton.setValue(" +");
        curr ? invertColor(list[curr]) : invertColor(list[0]);
        curr = 0;
    }

    return;
}

void ComboBox::invertColor(Button* button){
    Color tempColor = button->getTextColor();
    button->setTextColor(button->getBackgroundColor());
    button->setBackgroundColor(tempColor);
}

void ComboBox::draw(Graphics& g, int x, int y, size_t z){
    if(z == 0){
        Control::draw(g, x, y, z);
        showButton.draw(g, showButton.getLeft() + 1, showButton.getTop() + 1, z);
        text.draw(g, text.getLeft() + 1, text.getTop() + 1, z);
        if(show){
            for(unsigned int i = 0; i < list.size(); ++i){
                list[i]->draw(g, list[i]->getLeft() + 1, list[i]->getTop() + 1, z);
            }
        }
    }
}