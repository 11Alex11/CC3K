#ifndef _WEREWOLF__H__
#define _WEREWOLF__H__

class TextDisplay;
class Floor;
#include "enemy.h"

class Werewolf:public Enemy{

public:
	Werewolf(int x,int y,Floor * floor);
    virtual void draw(TextDisplay& td);
};

#endif

