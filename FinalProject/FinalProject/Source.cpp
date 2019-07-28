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
#include "../Controls/CheckList.h"
#include "../Controls/RadioBox.h"

int main(int argc, char** argv)
{
	Panel P(0, 0, new DoubleBorder, Color::White, Color::Black);
	Button Bt(0, 10, 10, new SingleBorder, Color::White, Color::Black, "Show");
	semMessageBox M(0, 0, 30, new DoubleBorder, Color::White, Color::Cyan, "Message", "Ok", "Cancel", &Bt);
	TextBox T(40, 0, 10, new SingleBorder, Color::White, Color::Cyan);
	ComboBox C(40, 10, new SingleBorder, Color::White, Color::Cyan);
	CheckList CL(60, 10, 20, new DoubleBorder, Color::Purple, Color::White);
	RadioBox R(50, 10, 15, new DoubleBorder, Color::Blue, Color::White);
	C.addToList("one");
	C.addToList("two");
	C.addToList("forty seven");
	CL.addToList("hello");
	CL.addToList("HELLO");
	CL.addToList("HeLlO");
	R.addToList("qwer");
	R.addToList("asdf");
	R.addToList("zxcv");
	P.addControl(&M);
	P.addControl(&Bt);
	P.addControl(&T);
	P.addControl(&C);
	P.addControl(&CL);
	P.addControl(&R);
	EventEngine e;
	e.run(P);
}