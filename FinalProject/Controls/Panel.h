#pragma once
#include "vector"
#include "../Common/Control.h"
#include "../Common/Border/Border.h"
#include "MouseListener.h"

using namespace std;

class Panel : public Control, public MouseListener {
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
        virtual void update(int x, int y);

    private:
        vector<Control*> controls;
};
