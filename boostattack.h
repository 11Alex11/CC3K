#ifndef _BOOSTATTACK_H_
#define _BOOSTATTACK_H_
#include "potion.h"
#include <string>
class Player;
class BoostAttack:public Potion{
	static bool seen;
public:
	static void resetBoostAttack();
	BoostAttack(int x, int y,Floor* floor);
	virtual void use(Player* player);
	virtual std::string observe();
};




#endif
