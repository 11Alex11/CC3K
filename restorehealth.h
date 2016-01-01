#ifndef _RESTOREHEALTH_H_
#define _RESTOREHEALTH_H_
#include "potion.h"
#include <string>
class Player;
class RestoreHealth:public Potion{
	static bool seen;
public:
	static void resetRestoreHealth();
	RestoreHealth(int x, int y,Floor* floor);
	virtual void use(Player* player);
	virtual std::string observe();
};




#endif
