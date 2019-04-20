#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <string>
#include <windows.h>

class CheckBox
{
    DWORD id;
    short x;
    short y;
    bool selected;
    bool focused;
    WORD color;
    WORD background;
    std::string value;

    public:

        //Constructor
        CheckBox(DWORD id, short x, short y, std::string value = "DEFAULT");

        //Getters
        DWORD getID() const;
        bool getSelected() const;
        bool getFocused() const;
        WORD getColor() const;
        WORD getBg() const; 
        HANDLE getCSB() const;
        std::string getValue() const;
        

        //Setters
        void setX(const short& x);
        void setY(const short& y);
        void setSelected(const bool& selected); 
        void setFocused(const bool& focused);

        void draw(HANDLE hCSB);
        void handleKeyboardEvent(KEY_EVENT_RECORD&);
        void handleMouseEvent(MOUSE_EVENT_RECORD&);

    private:
        


};

#endif