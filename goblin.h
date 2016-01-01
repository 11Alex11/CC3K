#ifndef _GOBLIN__H__
#define _GOBLIN__H__

class TextDisplay;
class Floor;
#include "enemy.h"

class Goblin:public Enemy{

public:
	Goblin(int x,int y,Floor* floor);
    virtual void draw(TextDisplay& td);
};

#endif