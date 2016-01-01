#ifndef _POISONHEALTH_H_
#define _POISONHEALTH_H_
#include "potion.h"
#include <string>
class Player;
class PoisonHealth:public Potion{
	static bool seen;
public:
	static void resetPoisonHealth();
	PoisonHealth(int x, int y,Floor* floor);
	virtual void use(Player* player);
	virtual std::string observe();
};




#endif
