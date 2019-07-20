#include "MouseListener.h"

MouseListener::MouseListener() : Control() {}

MouseListener::MouseListener(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    Control(left, top, width, height, border, textColor, backgroundColor) {}