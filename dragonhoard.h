#ifndef _DRAGONHOARD_H_
#define _DRAGONHOARD_H_
#include "entity.h"
#include "vector.h"
#include "treasure.h"
#include "dragon.h"
class Floor;
class Player;

class DragonHoard:public Treasure{
	bool dead;
public:
	friend Vector Dragon::tick(); //allow dragon to change bool dead
	DragonHoard(int x,int y,int value,Floor* floor);
	void setDragonDead();
	virtual bool canCollideWith(const Entity* entity);
};


#endif