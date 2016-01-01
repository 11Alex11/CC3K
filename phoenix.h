#ifndef _PHOENIX__H__
#define _PHOENIX__H__

class TextDisplay;
class Floor;
#include "enemy.h"

class Phoenix:public Enemy{

public:
	Phoenix(int x,int y,Floor* floor);
    virtual void draw(TextDisplay& td);
};

#endif