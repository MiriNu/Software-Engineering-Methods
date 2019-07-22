#pragma once
#include "string"
#include "../Common/Control.h"
#include "Label.h"
#include "Button.h"
#include "MouseListener.h"

class semMessageBox : public Control, public MouseListener {
    public:
        semMessageBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor, string message);
        ~semMessageBox() {};

        string getMessage();
        void setMessage(string message);

        virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft);
		virtual bool canGetFocus() { return true; };
        virtual void update(int x, int y);

    private:
        Label message;
        Button ok;
        Button cancel;
};
