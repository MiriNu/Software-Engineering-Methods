#pragma once
#include "../Controls/EntryBox.h"
//#include <string>

class CheckList: public Control
{   
    private:
        //need to check how many entries possible to add according to the panel size 
        vector<EntryBox> entries;
        vector<EntryBox> selectedValues;

    public:
        CheckList (short left, short top, short width, Border* border, Color textColor, Color backgroundColor, vector<string> entries);

        //Getter
        vector<EntryBox> getSelectedValues();

        //Add or remove from entries vector
        void addEntry(string value);
        void removeEntry(size_t index);

        //Add or remove from selectedValues vector AND entries vector
        bool addSelectedEntry(string value);
        bool removeSelectedEntry(string value);

        void selectIndex(size_t index);
        void deselectIndex(size_t index);
        void draw(Graphics& g, int x, int y, size_t z);

};