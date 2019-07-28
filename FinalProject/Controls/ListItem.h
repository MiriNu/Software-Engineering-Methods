#pragma once
#include "../Common/Control.h"
#include "../Common/Border/Border.h"
#include "../Controls/Button.h"

class ListItem : public Button {
    public:
        ListItem(short left, short top, short width, Color textColor, Color backgroundColor, string value);
        ~ListItem();

        void setSelectedString(string str) { selectedString = str; };
        void setUnselectedString(string str) { unselectedString = str; };
        bool getSelected() { return selected; };
        void setSelected(bool selected) { this->selected = selected; };

        virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft);
		virtual void keyDown(int keyCode, char charecter);
		virtual bool canGetFocus() { return true; };

    private:
        string selectedString;
        string unselectedString;
        bool selected;
};
