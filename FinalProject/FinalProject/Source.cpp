#include "../Common/Graphics.h"
#include "../Controls/textbox.h"
#include "../Common/EventEngine.h"
#include "../Controls/Panel.h"
#include "../Common/Border/Border.h"
#include "../Common/Border/DoubleBorder.h"
#include "../Common/Border/NullBorder.h"
#include "../Common/Border/SingleBorder.h"

<<<<<<< HEAD
int main(int argc, char** argv){

	TextBox l(12, 3, 3);
	EventEngine e;
	e.run(l);
=======
int main(int argc, char** argv)
{
	Border* B = new DoubleBorder;
	Border* B2 = new SingleBorder;
	Border* B3 = new NullBorder;
	Panel P(5, 5, 50, 20, B, Color::White, Color::Black);
	Panel P2(5, 5, 30, 10, B2, Color::Blue, Color::Black);
	Panel P3(1, 1, 10, 10, B3, Color::Green, Color::Black);
	Label l("panel 1");
	Label l2("panel 2");
	Label l3("panel 3");
	P3.addControl(&l3);
	P2.addControl(&l2);
	P2.addControl(&P3);
	P.addControl(&l);
	P.addControl(&P2);
	EventEngine e;
	e.run(P);

>>>>>>> 493d78468745dc7fe7288a4f19e47107ac9973b4
}