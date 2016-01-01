#ifndef _WOUNDDEFENCE_H_
#define _WOUNDDEFENCE_H_
#include "potion.h"
#include <string>
class Player;
class WoundDefence:public Potion{
	static bool seen;
public:
	static void resetWoundDefence();
	WoundDefence(int x, int y,Floor* floor);
	virtual void use(Player* player);
	virtual std::string observe();
};




#endif
