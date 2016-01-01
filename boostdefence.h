#ifndef _BOOSTDEFENCE_H_
#define _BOOSTDEFENCE_H_
#include "potion.h"
#include <string>
class Player;
class BoostDefence:public Potion{
	static bool seen;
public:
	static void resetBoostDefence();
	BoostDefence(int x, int y,Floor* floor);
	virtual void use(Player* player);
	virtual std::string observe();
};




#endif
