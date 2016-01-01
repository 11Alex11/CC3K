#include "wounddefence.h"
#include <string>
#include "player.h"
#include "potion.h"
bool WoundDefence::seen = false;
WoundDefence::WoundDefence(int x,int y,Floor* floor):Potion(x,y,-5,"WD",floor){}

void WoundDefence::resetWoundDefence(){
	seen = false;
}

//return name if used before
std::string WoundDefence::observe(){
	if(seen){
		return getName();
	}
	else{
		return "Unknown Potion";
	}
}
//give player defence(negative defence)
void WoundDefence::use(Player* player){
	player->giveDefence(value);
    seen = true;
	removePotion();
}
