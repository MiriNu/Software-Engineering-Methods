#include "NumericBox.h"

NumericBox:: NumericBox(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor, string Value) :
    Control(left, top, width, height, new SingleBorder(), textColor, backgroundColor),
    value(left + 10, top + 10, 2, 1, new SingleBorder(), textColor, backgroundColor, "0"),
    add(left + 5, top + 10, 2, 1, new SingleBorder(), textColor, backgroundColor, "+"),
    subtract(left + 15, top + 10, 2, 1, new SingleBorder(), textColor, backgroundColor, "-")
{
    add.addListener(this);
    add.addListener(this);

}
