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

int main(int argc, char** argv)
{
	Border* B = new DoubleBorder;
	Panel P(0, 0, 50, 20, B, Color::White, Color::Black);
	semMessageBox M(0, 0, 30, B, Color::White, Color::Cyan, "Message");
	P.addControl(&M);
	EventEngine e;
	e.run(P);
}