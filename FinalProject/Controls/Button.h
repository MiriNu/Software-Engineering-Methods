#pragma once
#include "vector"
#include "string"
#include "Label.h"
#include "MouseListener.h"

using namespace std;

class Button : public Label {
	public:
		Button(string value);
		Button(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor, string Value);

		bool addListener(MouseListener *listener);

		virtual void mousePressed(int x, int y, bool isLeft);

	private:
        vector<MouseListener*> listeners;
};