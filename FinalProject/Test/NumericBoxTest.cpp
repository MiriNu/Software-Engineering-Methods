#include <assert.h>
#include "../Controls/NumericBox.h"
#include "Test.h"
#include "../Common/Border/SingleBorder.h"
#include <iostream>

class NumericBoxTest : public Test {
    public:
        void runTest() {
            checkSetVal();
            checkValueRange();
            checkAdd();
            checkSub();
        }

    private:
        void checkSetVal() {
            NumericBox NB(0, 0, 10, 0, new SingleBorder, Color::White, Color::Black);
            assert(NB.getVal() == 0);
            NB.setVal(100);
            assert(NB.getVal() == 10);
            NB.setVal(-73);
            assert(NB.getVal() == 0);
            NB.setVal(5);
            assert(NB.getVal() == 5);
        }

        void checkValueRange() {
            NumericBox NB(0, 0, 1, 0, new SingleBorder, Color::White, Color::Black);
            assert(NB.getVal() == 0);
            NB.subFromVal();
            assert(NB.getVal() == 0);
            NB.addToVal();
            assert(NB.getVal() == 1);
            NB.addToVal();
            assert(NB.getVal() == 1);
        }

        void checkAdd() {
            NumericBox NB(0, 0, 2, 0, new SingleBorder, Color::White, Color::Black);
            assert(NB.getVal() == 0);
            NB.addToVal();
            assert(NB.getVal() == 1);
            NB.addToVal();
            assert(NB.getVal() == 2);
            NB.addToVal();
            assert(NB.getVal() == 2);
        }

        void checkSub() {
            NumericBox NB(0, 0, 2, 0, new SingleBorder, Color::White, Color::Black);
            assert(NB.getVal() == 0);
            NB.setVal(2);
            assert(NB.getVal() == 2);
            NB.subFromVal();
            assert(NB.getVal() == 1);
            NB.subFromVal();
            assert(NB.getVal() == 0);
            NB.subFromVal();
            assert(NB.getVal() == 0);
        }
};

int main(int argc, char* argv[]) {
    NumericBoxTest nbt;
    nbt.runTest();
    char c;
    cin >> c;
    return 0;
}