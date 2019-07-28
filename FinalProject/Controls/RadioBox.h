#pragma once
#include "CheckList.h"

class RadioBox : public CheckList {
    public:
        RadioBox(short left, short top, short width, Border* border, Color textColor, Color backgroundColor);
        ~RadioBox();

        virtual void addToList(string item);
        string getSelectedItem() { return items[selectedIndex]->getValue(); };
        bool setSelectedItem(int index);
        bool clearSelection();

		virtual void keyDown(int keyCode, char charecter);
        virtual void update(int x, int y, string s);

    private:
        int selectedIndex;

        bool addSelectedItem(string item) { return false; };
        bool removeSelectedItem(string item) { return false; };
        void getSelectedItems(vector<string>& selected) {};
};
