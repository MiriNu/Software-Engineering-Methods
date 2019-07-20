#pragma once
#include "../Common/Control.h"

using namespace std;

class MouseListener : public Control {
	public:
		MouseListener();
		MouseListener(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor);

		virtual void update() = 0;
};