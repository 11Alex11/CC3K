#ifndef _DOORWAY_H_
#define _DOORWAY_H_
#include "entity.h"
class TextDisplay;
class Floor;

class Doorway:public Entity{

public: 
    Doorway( int x,int y,Floor* floor);
	virtual void draw(TextDisplay& td);
    bool canCollideWith(const Entity* entity);
};


#endif
