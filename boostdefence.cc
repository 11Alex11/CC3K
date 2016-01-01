#include "boostdefence.h"
#include <string>
#include "player.h"
#include "potion.h"
bool BoostDefence::seen = false;
BoostDefence::BoostDefence(int x,int y,Floor* floor):Potion(x,y,5,"BD",floor){}

void BoostDefence::resetBoostDefence(){
	seen = false;
}
//return name if used before
std::string BoostDefence::observe(){
	if(seen){
		return getName();
	}
	else{
		return "Unknown Potion";
	}
}
//give player defence
void BoostDefence::use(Player* player){
	player->giveDefence(value);
    seen = true;
	removePotion();
}
