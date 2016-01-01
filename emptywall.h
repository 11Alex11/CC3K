#ifndef _EMPTYWALL_H_
#define _EMPTYWALL_H_
#include "entity.h"
class TextDisplay;
class Floor;
class EmptyWall:public Entity{

public: 
    EmptyWall(int x,int y,Floor* floor);
	virtual void draw(TextDisplay& td);
};


#endif
