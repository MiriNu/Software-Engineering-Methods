#include "../Common/Graphics.h"
#include "../Controls/textbox.h"
#include "../Common/EventEngine.h"
#include "../Controls/Panel.h"
#include "../Common/Border/Border.h"
#include "../Common/Border/DoubleBorder.h"
#include "../Common/Border/NullBorder.h"
#include "../Common/Border/SingleBorder.h"
#include "../Controls/Label.h"
#include "../Controls/MessageBox.h"
#include "../Controls/Button.h"
#include "../Controls/textbox.h"
#include "../Controls/ComboBox.h"

int main(int argc, char** argv)
{
	Panel P(0, 0, new DoubleBorder, Color::White, Color::Black);
	Button Bt(0, 10, 10, new SingleBorder, Color::White, Color::Black, "Show");
	semMessageBox M(0, 0, 30, new DoubleBorder, Color::White, Color::Cyan, "Message", "Ok", "Cancel", &Bt);
	TextBox T(40, 0, 10, new SingleBorder, Color::White, Color::Cyan);
	ComboBox C(40, 10, new SingleBorder, Color::White, Color::Cyan);
	C.addToList("one");
	C.addToList("two");
	C.addToList("forty seven");
	P.addControl(&M);
	P.addControl(&Bt);
	P.addControl(&T);
	P.addControl(&C);
	EventEngine e;
	e.run(P);
}