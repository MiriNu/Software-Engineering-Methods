#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <string>
#include <windows.h>

class CheckBox
{
    SHORT x;
    SHORT y;
    bool selected;
    bool focused;
    WORD color;
    WORD background;
    std::string value;

    public:

        //Constructor
        CheckBox(SHORT x, SHORT y, std::string value = "DEFAULT");

        //Getters
		SHORT getY() const;
		SHORT getX() const;
        bool getSelected() const;
        bool getFocused() const;
        WORD getColor() const;
        WORD getBg() const; 
        std::string getValue() const;
        
        //Setters
		void setY(const SHORT y);
		void setX(const SHORT x);
        void setSelected(const bool selected); 
        void setFocused(const bool focused);
		void setValue(const std::string value);

		//Draw a single CB on screen
        void draw(HANDLE hCSB);
        

};

#endif