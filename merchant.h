#ifndef _MERCHANT__H__
#define _MERCHANT__H__

class TextDisplay;
class Floor;
#include "enemy.h"
#include "vector.h"


class Merchant:public Enemy{
	static bool hostile;
public:
	static void resetMerchant();
	Merchant(int x,int y,Floor* floor);
    virtual void draw(TextDisplay& td);
	virtual int strike(int attackPower); //override enemy strike
	virtual Vector tick(); //override enemy tick
};

#endif
