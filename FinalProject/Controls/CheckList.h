#pragma once
#include <vector>
#include "ListItem.h"
#include "MouseListener.h"

class CheckList : public Control, public MouseListener {
    public:
        CheckList(short left, short top, short width, Border* border, Color textColor, Color backgroundColor);
        ~CheckList();

        virtual void addToList(string item);
        bool addSelectedItem(string item);
        bool removeSelectedItem(string item);
        void getSelectedItems(vector<string>& selected);
        void invertColors(ListItem* item);

        virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft);
		virtual void keyDown(int keyCode, char charecter);
		virtual void getAllControls(vector<Control*>* controls);
		virtual bool canGetFocus() { return true; };
		virtual int getFocusIndex();
        virtual void update(int x, int y, string s);

    protected:
        vector<ListItem*> items;
        vector<string> selectedItems;
        int focusIndex;
};
