#include "poisonhealth.h"
#include <string>
#include "player.h"
#include "potion.h"
bool PoisonHealth::seen = false;
PoisonHealth::PoisonHealth(int x,int y,Floor* floor):Potion(x,y,-10,"PH",floor){}
void PoisonHealth::resetPoisonHealth(){
	seen = false;
}
//return name if used before
std::string PoisonHealth::observe(){
        if(seen){
		return getName();
	}
	else{
		return "Unknown Potion";
	}
}
//give player health(negative health)
void PoisonHealth::use(Player* player){
	player->giveHealth(value);
        seen = true;
	removePotion();
}
