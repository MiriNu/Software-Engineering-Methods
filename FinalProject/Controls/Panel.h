#pragma once
#include "vector"
#include "Composite.h"
#include "../Common/Border/Border.h"

using namespace std;

class Panel : public Control {
    public:
        Panel();
        Panel(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor);
        ~Panel();

        bool addControl(Control* control);
        Control* getControl(int index);
        bool focusInPanel();

        virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft);
		virtual void keyDown(int keyCode, char charecter);
		virtual void getAllControls(vector<Control*>* controls);
		virtual bool canGetFocus();

    private:
        vector<Control*> controls;
};