#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <string>
#include <windows.h>
#include <vector>
#include "checkbox.h"
class CheckList
{
    std::vector<CheckBox> cb;
    SHORT x;
    SHORT y;

    public:

        //Constructor
        CheckList( SHORT x, SHORT y);

        //Getters
	    SHORT getX() const;
        SHORT getY() const;
		//Only one cb should be focused at each time, this function provides the pos of said cb
        int getFocusedPos() const;
		//Get a vector of selected attributes
		std::vector<int> getSelectedPos() const;
		//Get the width of the cl according to the longest cb value
		int getCLWidth() const;
		//Get the height of the cl according to the size of cb
		int getCLheight() const;

        //Setters
        void setCoord(const SHORT x, const SHORT y);

		//Event handlers
        void handleKeyboardEvent(KEY_EVENT_RECORD&, HANDLE hCSB);
        void handleMouseEvent(MOUSE_EVENT_RECORD&, HANDLE hCSB);
        
		//Add cb by value
        void addCheckBox (const std::string value);
		//Delete cb by position
        void deleteCheckBox (SHORT pos);
		//Draw all existing checkboxes on a given screen
        void draw(HANDLE hCSB);
        

    private:

};

#endif