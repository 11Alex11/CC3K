#include "restorehealth.h"
#include <string>
#include "player.h"
#include "potion.h"
bool RestoreHealth::seen = false;
RestoreHealth::RestoreHealth(int x,int y,Floor* floor):Potion(x,y,10,"RH",floor){}
void RestoreHealth::resetRestoreHealth(){
	seen = false;
}

//return name if used before
std::string RestoreHealth::observe(){
	if(seen){
		return getName();
	}
	else{
		return "Unknown Potion";
	}
}
//give player health
void RestoreHealth::use(Player* player){
	player->giveHealth(value);
    seen = true;
	removePotion();
}
