#ifndef _HORIZONTALWALL_H_
#define _HORIZONTALWALL_H_
#include "entity.h"
class TextDisplay;
class Floor; 

class HorizontalWall:public Entity{

public:
    HorizontalWall( int x,int y,Floor* floor);
	virtual void draw(TextDisplay& td);
};


#endif
