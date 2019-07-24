#include "ComboBox.h"
#include "../Common/Border/SingleBorder.h"

ComboBox::ComboBox(short left, short top, Border* border, Color textColor, Color backgroundColor):
    Control(left, top, 20, 20, border, textColor, backgroundColor),
    showButton(left + 1, top + 1, 10, new SingleBorder(), textColor, backgroundColor, "Show List"),
    text(left + 1, top + 5, 10, new SingleBorder(), textColor, backgroundColor, ""),
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
    list.push_back(new Button(left + 1, text.getTop() + ( (1 + list.size()) * 3), 10, new SingleBorder(), Color::White, Color::Black, toAdd));
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
        if(keyCode == VK_RETURN){
            text.setValue(list[curr]->getValue());
            show = false;
            selected = curr;
            invertColor(list[curr]);
            curr = 0;
            return;
        }

        if(keyCode == VK_UP){
            if(curr == 0)
                return;
            
            invertColor(list[curr]);
            --curr;
            invertColor(list[curr]);
            return;
        }

        if(keyCode == VK_DOWN){
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

void ComboBox::update(int x, int y){
    int  showL = showButton.getLeft(), showT = showButton.getTop(), showW = showButton.getWidth(), showH = showButton.getHeight();

    if(x >= showL && x <= showL + showW && y >= showT && y <= showT + showH) {
        show = !show;
        if (curr == 0){
            invertColor(list[0]);
            return;
        }

        invertColor(list[curr]);
        curr = 0;
        return;
    }

    if(show){
        for(unsigned int i = 0; i < list.size(); ++i){
            int  ButtonL = list[i]->getLeft(), ButtonT = list[i]->getTop(), ButtonW = list[i]->getWidth(), ButtonH = list[i]->getHeight();
            std::cout << "x: " << x << "y: " << y << std::endl << "buttonL: " << ButtonL << " ButtonT: " << ButtonT << std::endl;
            if(x >= ButtonL && x <= ButtonL + ButtonW && y >= ButtonT && y <= ButtonT + ButtonH) {
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
}