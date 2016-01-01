#ifndef _STAIRS_H_
#define _STAIRS_H_
#include "entity.h"
class TextDisplay;
class Floor;


class Stairs:public Entity{

public: 
	Stairs( int x,int y,Floor* floor);
	virtual void draw(TextDisplay& td);
	bool canCollideWith(const Entity* entity);
};


#endif