#include "ComboBox.h"
#include "../Common/Border/SingleBorder.h"

ComboBox::ComboBox(short left, short top, Border* border, Color textColor, Color backgroundColor):
    Control(left, top, 20, 10, border, textColor, backgroundColor),
    text(left + 5, top + 1, 25, 1, new SingleBorder(), textColor, backgroundColor, ""),
    showButton(left + 1, top + 1, 15, 1, new SingleBorder(), textColor, backgroundColor, "Show List"),
    selected(0), show(false), curr(0)
{
    showButton.addListener(this);
}

int ComboBox::getSelected(){
    return selected;
}

void ComboBox::setSelected(int index){
    selected = index;
}

void ComboBox::addToList(string toAdd){
    Button newButton(left, top + list.size() + 1, 25, 1, new SingleBorder(), Color::White, Color::Black, toAdd);
    list.push_back(newButton);
}

void ComboBox::mousePressed(int x, int y, bool isLeft){
    showButton.mousePressed(x, y, isLeft);
    if(show){
        for(unsigned int i = 0; i < list.size(); ++i)
            list[i].mousePressed(x, y, isLeft);
    }
}

void ComboBox::keyDown(int keyCode, char character){
/* check if enter, if yes, update value in text. if key down/up, update curr to index of pressed */
    if("up"){
        Color temp = list[curr].getTextColor();
        setTextColor(list[curr].getBackgroundColor());
        setBackgroundColor(temp);
        --curr;
        Color temp = list[curr].getTextColor();
        setTextColor(list[curr].getBackgroundColor());
        setBackgroundColor(temp);
    }

    if("down"){
        Color temp = list[curr].getTextColor();
        setTextColor(list[curr].getBackgroundColor());
        setBackgroundColor(temp);
        ++curr;
        Color temp = list[curr].getTextColor();
        setTextColor(list[curr].getBackgroundColor());
        setBackgroundColor(temp);
    }
}
void ComboBox::update(int x, int y){}

void ComboBox::draw(Graphics& g, int x, int y, size_t z){
    if(z == 0){
        Control::draw(g, x, y, z);
        showButton.draw(g, showButton.getLeft(), showButton.getTop(), z);
        text.draw(g, text.getLeft(), text.getTop(), z);
        if(show){
            for(unsigned int i = 0; i < list.size(); ++i){
                list[i].draw(g, list[i].getLeft(), list[i].getTop(), z);
            }
        }
    }
}