#include "textdisplay.h"
#include <iostream>
#include <fstream>
//allocate space for the games board and the players statistics
TextDisplay::TextDisplay():floorHeight(25),floorWidth(79),textHeight(5),textWidth(79){
	theBoard = new char*[floorHeight];
	for(int i=0;i<floorHeight;i++){
	theBoard[i]=new char[floorWidth];
	}

	theText = new char*[textHeight];
	for(int i=0;i<textHeight;i++){
		theText[i]=new char[textWidth];
                
	}
                
        clearTheText();
        currentFooterRow = 0;
}

// each entity will call this, updating the board
void TextDisplay::notify(int row,int col,char symbol){
  theBoard[row][col]=symbol;
        
}


void TextDisplay::writeStringToFooter(std::string s, int xoffset, int yoffset)
{
  for (int i = 0; (i < s.size()) && (i < textWidth); i++)
    {
      theText[yoffset][xoffset + i] = s[i];
    }
  if ((s.size() + xoffset) > textWidth)
    {
      theText[yoffset][textWidth - 1] = '.';
      theText[yoffset][textWidth - 2] = '.';
      theText[yoffset][textWidth - 3] = '.';
    }

}

// adds a line to the footer
void TextDisplay::addFooterLine(std::string line)
{
  // for (int i = 0; (i < line.size()) && (i < textWidth); i++)
  //   {
  //     theText[currentFooterRow][i] = line[i];
  //   }
  // if (line.size() > textWidth)
  //   {
  //     theText[currentFooterRow][textWidth - 1] = '.';
  //     theText[currentFooterRow][textWidth - 2] = '.';
  //     theText[currentFooterRow][textWidth - 3] = '.';
  //   }
  // currentFooterRow++;
  writeStringToFooter(line, 0, currentFooterRow);
  currentFooterRow++;
}

void TextDisplay::clearTheText()
{
  for (int x = 0; x < textHeight; x++)
    {
      for (int y = 0; y < textWidth; y++)
        {
          theText[x][y] = ' ';
        }
    }
  currentFooterRow = 0;
}

//display the the game board and the players statistics
std::ostream& operator<<(std::ostream &out, TextDisplay &td){
	for(int i=0; i< td.floorHeight;i++){
		for(int j=0; j< td.floorWidth;j++){
			out << td.theBoard[i][j];
		}
		out << '\n';
	}
	for(int i=0; i< td.textHeight;i++){
		for(int j=0; j< td.textWidth;j++){
			out << td.theText[i][j];
		}
		out << '\n';
	}
        td.clearTheText();
	return out;
}

//delete all allocated memory for the game board and player
//statistics text 
TextDisplay::~TextDisplay(){
	for(int i = 0;i<floorHeight;i++){
		delete [] theBoard[i];
	}
	for(int i=0;i<textHeight;i++){
		delete [] theText[i];
	}
	delete [] theBoard;
	delete [] theText;
}
