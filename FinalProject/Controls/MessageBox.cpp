#include "MessageBox.h"
#include "../Common/Border/SingleBorder.h"
#include "../Common/Border/NullBorder.h"

semMessageBox::semMessageBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor, string message) :
    Control(left, top, width, 7, border, textColor, backgroundColor),
    message(Label((width - message.size()) / 2, 0, message.size(), 1, new NullBorder, textColor, backgroundColor, message)),
    ok(Button(0, 4, width / 3, 1, new SingleBorder, Color::White, Color::Green, "Ok")),
    cancel(Button((width - (width / 3) - 2), 4, width / 3, 1, new SingleBorder, Color::White, Color::Red, "Cancel")) {
        ok.addListener(this);
        cancel.addListener(this);
}

string semMessageBox::getMessage() {
    return message.getValue();
}

void semMessageBox::setMessage(string message) {
    this->message.setValue(message);
}

void semMessageBox::draw(Graphics& g, int x, int y, size_t z) {
    int relativeX, relativeY;
    if(z == 0) {
        Control::draw(g, x, y, z);
        relativeX = message.getLeft();
        relativeY = message.getTop();
        message.draw(g, x + relativeX + 1, y + relativeY + 1, z);
        relativeX = ok.getLeft();
        relativeY = ok.getTop();
        ok.draw(g, x + relativeX + 1, y + relativeY + 1, z);
        relativeX = cancel.getLeft();
        relativeY = cancel.getTop();
        cancel.draw(g, x + relativeX + 1, y + relativeY + 1, z);
    }
}

void semMessageBox::mousePressed(int x, int y, bool isLeft) {
    ok.mousePressed(x - getLeft() - 1, y - getTop() - 1, isLeft);
    cancel.mousePressed(x - getLeft() - 1, y - getTop() - 1, isLeft);
}

void semMessageBox::update(int x, int y) {
    int okl = ok.getLeft(), okt = ok.getTop(), okw = ok.getWidth(), okh = ok.getHeight();
    int canl = cancel.getLeft(), cant = cancel.getTop(), canw = cancel.getWidth(), canh = cancel.getHeight();
    if(x >= okl && x <= okl + okw && y >= okt && y <= okt + okh) {
        setMessage("OK");
    }
    else if(x >= canl && x <= canl + canw && y >= cant && y <= cant + canh) {
        setMessage("CANCEL");
    }
}
