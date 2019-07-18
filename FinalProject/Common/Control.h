#pragma once
#include <vector>
#include "Graphics.h"
#include "Border/Border.h"

using namespace std;

class Control {
	public:
		Control();
		Control(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor);
		virtual ~Control() = 0;

		static Control* getFocus() { return focusedControl; };
		static void setFocus(Control& control);

		virtual short getLeft() { return left; };
		virtual short getTop() { return top; };
		virtual short getWidth() { return width; };
		virtual short getHeight() { return height; };
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
		virtual void focus() {};
		virtual void unfocus() {};

	protected:
		static Control* focusedControl;

		short left;
		short top;
		short width;
		short height;
		Border* border;
		Color textColor;
		Color backgroundColor;
};
