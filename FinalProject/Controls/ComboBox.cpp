#include "ComboBox.h"
#include "../Common/Border/SingleBorder.h"

ComboBox::ComboBox(short left, short top, Border* border, Color textColor, Color backgroundColor):
    Control(left, top, 20, 20, border, textColor, backgroundColor),
    showButton(left + 15, top + 1, 1, new SingleBorder(), textColor, backgroundColor, " +"),
    text(left + 1, top + 1, 10, new SingleBorder(), textColor, backgroundColor, ""),
    selected(0), show(false), curr(0)
{
    showButton.addListener(this);
    setFocus(*this);
}

int ComboBox::getSelected(){
    return selected;
}

void ComboBox::setSelected(int index){
    selected = index;
}

void ComboBox::addToList(string toAdd){
    Button* toAdd = new Button(left + 1, text.getTop() + ( (1 + list.size()) * 3), 10, new SingleBorder(), Color::White, Color::Black, toAdd);
    list.push_back(toAdd);
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
            selected = curr;
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
    std::cout << "x: " << x << " y: " << y << std::endl;
    if(s.compare(" +") == 0 || s.compare(" -") == 0){
        show = !show;

        show ? showButton.setValue(" -") : showButton.setValue(" +");
        curr ? invertColor(list[curr]) : invertColor(list[0]);

        curr = 0;
        return;
    }

    else if(show){
        for(unsigned int i = 0; i < list.size(); ++i){
            if(s == list[i]->getValue()){
                text.setValue(list[i]->getValue());
                show = false;
                return;
            }
        }
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
        showButton.draw(g, showButton.getLeft(), showButton.getTop(), z);
        text.draw(g, text.getLeft(), text.getTop(), z);
        if(show){
            for(unsigned int i = 0; i < list.size(); ++i){
                list[i]->draw(g, list[i]->getLeft(), list[i]->getTop(), z);
            }
        }
    }
    g.moveTo(25, 25);
}