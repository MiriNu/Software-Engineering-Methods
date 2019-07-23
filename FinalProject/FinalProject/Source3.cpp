#include "../Common/Graphics.h"
#include "../Controls/textbox.h"
#include "../Common/EventEngine.h"
#include "../Controls/Panel.h"
#include "../Common/Border/Border.h"
#include "../Common/Border/DoubleBorder.h"
#include "../Common/Border/NullBorder.h"
#include "../Common/Border/SingleBorder.h"
#include "../Controls/Label.h"
#include "../Controls/NumericBox.h"
#include "../Controls/MessageBox.h"

int main(int argc, char** argv)
{
	NumericBox t(5, 5, 5, 0, new SingleBorder(), Color::White, Color::Black);
	EventEngine e;
	e.run(t);
}