#include "boostattack.h"
#include <string>
#include "player.h"
#include "potion.h"
bool BoostAttack::seen = false;
BoostAttack::BoostAttack(int x,int y,Floor* floor):Potion(x,y,5,"BA",floor){}

void BoostAttack::resetBoostAttack(){
	seen = false;
}

//return name if used before
std::string BoostAttack::observe(){
	if(seen){
		return getName();
	}
	else{
		return "Unknown Potion";
	}
}
//give player attack
void BoostAttack::use(Player* player){
	player->giveAttack(value);
    seen = true;
	removePotion();
}
