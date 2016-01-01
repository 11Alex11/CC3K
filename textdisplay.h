#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>


class TextDisplay {
	const int floorHeight;
	const int floorWidth;
	const int textHeight;
	const int textWidth;
    char **theBoard;
    char **theText;
    int currentFooterRow;
    
    void clearTheText();
public:
    TextDisplay();
    void notify(int x, int y, char symbol); // modify theBoard at x,y with symbol
    void addFooterLine(std::string line);
    void writeStringToFooter(std::string s, int xoffset, int yoffset);

    ~TextDisplay();

    friend std::ostream &operator<<(std::ostream &out, TextDisplay &td);
};

#endif
