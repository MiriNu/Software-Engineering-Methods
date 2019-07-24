#pragma once
#include "string"
#include "../Common/Control.h"
#include "Button.h"
#include "MouseListener.h"
#include <vector>

class ComboBox : public Control, public MouseListener {
    public:
        ComboBox(short left, short top, Border* border, Color textColor, Color backgroundColor);
        ~ComboBox() {};

        int getSelected();
        void setSelected(int index);
        void addToList(string toAdd);
        void draw(Graphics& g, int x, int y, size_t z);
		void mousePressed(int x, int y, bool isLeft);
        void keyDown(int keyCode, char character);
        void invertColor(Button* button);
        string getValue(){return text.getValue();}

		bool canGetFocus() { return true; };
        void update(int x, int y, string s);

    private:
        vector<Button*> list;
        Button showButton;
        Label text;
        bool show;
        int selected;
        int curr;
};
