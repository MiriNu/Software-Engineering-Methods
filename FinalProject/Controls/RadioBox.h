#include "../Common/Control.h"
#include <string>


using namespace std;

class RadioBox: public Control
{   
    private:
        vector<string> entries;
    public:
        RadioBox (int height, int width, vector<string> entries);
        size_t GetSelectedIndex();
        void SetSelectedIndex(size_t index);
        void draw(Graphics& g, int x, int y, size_t z);

};