#ifndef _TROLL__H__
#define _TROLL__H__

class TextDisplay;
class Floor;
#include "enemy.h"

class Troll:public Enemy{

public:
	Troll(int x,int y,Floor* floor);
    virtual void draw(TextDisplay& td);
};

#endif