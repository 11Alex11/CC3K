#ifndef _CHAMBERFLOOR_H_
#define _CHAMBERFLOOR_H_
#include "entity.h"
class TextDisplay;
class Floor;
 
class ChamberFloor:public Entity{

public:
    ChamberFloor( int x,int y,Floor* floor);
	virtual void draw(TextDisplay& td);
    bool canCollideWith(const Entity* entity);
};


#endif
