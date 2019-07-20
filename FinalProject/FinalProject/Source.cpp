#include "../Common/Graphics.h"
#include "../Controls/textbox.h"
#include "../Common/EventEngine.h"

int main(int argc, char** argv){

	TextBox l(12, 3, 3);
	EventEngine e;
	e.run(l);
}