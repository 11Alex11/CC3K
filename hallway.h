#ifndef _HALLWAY_H_
#define _HALLWAY_H_
#include "entity.h"
class TextDisplay;
class Floor;
class Hallway:public Entity{

public: 
        Hallway( int x,int y,Floor* floor);
		bool canCollideWith(const Entity* entity);
		virtual void draw(TextDisplay& td);
};


#endif
