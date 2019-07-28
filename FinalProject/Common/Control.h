#pragma once
#include <vector>
#include <typeinfo>
#include "Graphics.h"
#include "Border/Border.h"

using namespace std;

class Control {
	public:
		Control(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor);
		virtual ~Control() = 0;

		static Control* getFocus() { return focusedControl; };
		static void setFocus(Control& control);
		static bool getMessageBoxLock() { return messageBoxLock; };
		static void setMessageBoxLock(bool isLocked);

		virtual short getLeft() { return left; };
		virtual short getTop() { return top; };
		virtual short getWidth() { return width; };
		virtual short getHeight() { return height; };
		Border* getBorder() { return border; };
		Color getTextColor() { return textColor; };
		Color getBackgroundColor() { return backgroundColor; };

		virtual void setLeft(short left) { this->left = left; };
		virtual void setTop(short top) { this->top = top; };
		virtual void setWidth(short width) { this->width = width; };
		virtual void setHeight(short height) { this->height = height; };
		void setBorder(Border* border);
		void setTextColor(Color textColor) { this->textColor = textColor; };
		void setBackgroundColor(Color backgroundColor) { this->backgroundColor = backgroundColor; };

		virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft) {};
		virtual void keyDown(int keyCode, char charecter) {};
		virtual void getAllControls(vector<Control*>* controls) {};
		virtual bool canGetFocus() { return false; };
		virtual int getFocusIndex() { return -1; };

	protected:
		static Control* focusedControl;
		static bool messageBoxLock;

		short left;
		short top;
		short width;
		short height;
		Border* border;
		Color textColor;
		Color backgroundColor;
};
