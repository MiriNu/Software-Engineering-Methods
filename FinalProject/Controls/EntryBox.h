#pragma once
#include <string>
#include "../Common/Control.h"
#include "Button.h"
#include "Label.h"
#include "../Common/Graphics.h"
#include "../Common/Border/Border.h"
#include "MouseListener.h"

class EntryBox: public Control, public MouseListener 
{   
    private:
        Label value;
        Button selector;
        bool isSelected;
        bool isFocused; 
        
    public:
        EntryBox (short left, short top, short width, Border* border, Color textColor, Color backgroundColor, std::string value);
        ~EntryBox() {};
        void draw(Graphics& g, int x, int y, size_t z);
        void mousePressed(int x, int y, bool isLeft);
        void update(int x, int y, string s);
        void invertColor(Control* lbl);

         //Getters
        bool getSelected();
        bool getFocused();
        std::string getValue();
        
        //Setters
        void setSelected(const bool selected); 
        void setFocused(const bool focused);
        

};