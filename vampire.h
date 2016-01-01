#ifndef _VAMPIRE__H__
#define _VAMPIRE__H__

class TextDisplay;
class Floor;
#include "enemy.h"

class Vampire:public Enemy{

public:
	Vampire(int x,int y,Floor* floor);
    virtual void draw(TextDisplay& td);
};

#endif