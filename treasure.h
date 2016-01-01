#ifndef _TREASURE_H_
#define _TREASURE_H_
#include "entity.h"
#include "vector.h"
class Floor;
class Player;
class Treasure:public Entity{
	int value;
public:
	Treasure(int x,int y,int value,Floor* floor);
	virtual void draw(TextDisplay &td);
	int getValue();
	virtual bool canCollideWith(const Entity* entity);
	void use(Player& player);
};


#endif