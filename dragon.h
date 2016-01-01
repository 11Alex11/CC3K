#ifndef _DRAGON__H__
#define _DRAGON__H__

class TextDisplay;
class Floor;
#include "enemy.h"
#include "vector.h"
class DragonHoard;

class Dragon:public Enemy{
	DragonHoard* hoard;
public:
	void setHoard(DragonHoard* hoard);
	Dragon(int x,int y,DragonHoard* hoard,Floor* floor);
    virtual void draw(TextDisplay& td);
	virtual int strike(int attackPower); //override enemy strike
	virtual Vector tick(); //override entity tick
};

#endif