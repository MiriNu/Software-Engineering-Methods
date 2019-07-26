#pragma once
#include "string"
#include "../Common/Control.h"
#include "Label.h"
#include "Button.h"
#include "MouseListener.h"

class semMessageBox : public Control, public MouseListener {
    public:
        semMessageBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor, string message, string ok, string cancel, Button* showButton);
        ~semMessageBox() {};

        string getMessage();
        void setMessage(string message);
        string getReturnValue() { return returnValue; };
        void setShowButton(Button *button);

        virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft);
        virtual void update(int x, int y, string s);

    private:
        Label message;
        Button ok;
        Button cancel;
        string returnValue;
        Button* showButton;
        bool show;
};
