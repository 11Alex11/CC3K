#ifndef _VERTICALWALL_H_
#define _VERTICALWALL_H_
#include "entity.h"
class TextDisplay;
class Floor;

class VerticalWall:public Entity{

public: 
    VerticalWall( int x,int y,Floor* floor);
	virtual void draw(TextDisplay& td);
	
};


#endif
