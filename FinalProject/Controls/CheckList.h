#include "../Common/Control.h"
#include "../Controls/Label.h"
#include "../Controls/Button.h"
#include <string>

using namespace std;

typedef struct {
    Label value;
    Button selector;
    bool isSelected;
} Entry;

// Need class Entry: public Button 
class CheckList: public Control
{   
    private:
        //need to check how many entries possible to add according to the panel size 
        vector<Entry> entries;
        vector<Entry> selectedEntries;
        string value; 

    public:
        CheckList (int height, int width, vector<Entry> entries);
        vector<size_t> GetSelectedIndices();
        void addEntry(Label value);
        void removeEntry(size_t index);
        void selectIndex(size_t index);
        void deselectIndex(size_t index);
        void draw(Graphics& g, int x, int y, size_t z);

};