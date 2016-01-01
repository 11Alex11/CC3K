#ifndef _ENEMY__H__
#define _ENEMY__H__
#include "textdisplay.h"
#include "entity.h"
#include "vector.h"
class Enemy:public Entity{
protected:
	int health,attack,defence;
public: 
	Enemy( int health,int attack,int defence,int x,int y,std::string name,Floor*floor);
	virtual int strike(int attackPower); // this entity is being attacked
	virtual Vector tick();
	virtual ~Enemy()=0;
	virtual Vector move();
	int getHealth();
    
};

#endif

