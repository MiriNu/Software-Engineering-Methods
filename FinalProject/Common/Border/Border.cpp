#include "Border.h"

Border::Border() {}

Border::Border(char topLeft, char topRight, char bottomLeft, char bottomRight, char horizontal, char vertical) :
    topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight), horizontal(horizontal),
    vertical(vertical) {}

Border::~Border() {}

void Border::drawBorder(Graphics& g, short left, short top, short width, short height) {
    string line(width, horizontal);
    string space(width, ' ');
    g.moveTo(left, top);
    cout << topLeft << line << topRight;
    for(int i = 1; i < height - 1; ++i) {
        g.moveTo(left, top + i);
        cout << vertical << space << vertical;
    }
    g.moveTo(left, top + height - 1);
    cout << bottomLeft << line << bottomRight;
}
