#pragma once
#include "vector"
#include "../Common/Control.h"
#include "../Common/Border/Border.h"

using namespace std;

class Panel : public Control {
    public:
        Panel(short left, short top, Border* border, Color textColor, Color backgroundColor);
        ~Panel();

        bool addControl(Control* control);
        Control* getControl(int index);
        int getFocusIndex();

        virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft);
		virtual void keyDown(int keyCode, char charecter);
		virtual void getAllControls(vector<Control*>* controls);

    private:
        vector<Control*> controls;
        int focusIndex;

        void calculateWidthAndHeight();
};
