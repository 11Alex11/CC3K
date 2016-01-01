#ifndef _WOUNDATTACK_H_
#define _WOUNDATTACK_H_
#include "potion.h"
#include <string>
class Player;
class WoundAttack:public Potion{
	static bool seen;
public:
	static void resetWoundAttack();
	WoundAttack(int x, int y,Floor* floor);
	virtual void use(Player* player);
	virtual std::string observe();
};




#endif
