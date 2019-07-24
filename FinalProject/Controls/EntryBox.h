#pragma once
#include "../Common/Control.h"
#include "Button.h"
#include "Label.h"
#include "../Common/Graphics.h"
#include "../Common/Border/SingleBorder.h"
#include "MouseListener.h"

class EntryBox: public Control, public MouseListener 
{   
    private:
        Label value;
        Button selector;
        bool isSelected;
        bool isFocused; 

    public:
        EntryBox (string value);
        void draw(Graphics& g, int x, int y, size_t z);
        
         //Getters
        bool getSelected() const;
        bool getFocused() const;
        std::string getValue() const;
        
        //Setters
        void setSelected(const bool selected); 
        void setFocused(const bool focused);
		void setValue(const std::string value);
        

};