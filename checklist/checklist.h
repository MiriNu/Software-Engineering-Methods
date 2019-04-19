#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <string>
#include <windows.h>
#include <vector>
#include "checkbox.h"
class CheckList
{
    HANDLE hCSB;
    std::vector<CheckBox> cb;
    short x;
    short y;

    public:

        //Constructor
        CheckList( short x, short y);

        //Getters
	    short getX() const;
        short getY() const;

        //Setters
        void setX(const short& x);
        void setY(const short& y);

        void addCheckBox (const std::string value);
        void deleteCheckBox (DWORD id);
        void draw(HANDLE hCSB);

    private:

};

#endif