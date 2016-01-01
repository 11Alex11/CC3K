#include "woundattack.h"
#include <string>
#include "player.h"
#include "potion.h"
bool WoundAttack::seen = false;
WoundAttack::WoundAttack(int x,int y,Floor* floor):Potion(x,y,-5,"WA",floor){}

void WoundAttack::resetWoundAttack(){
	seen = false;
}

//return name if used before
std::string WoundAttack::observe(){
	if(seen){
		return getName();
	}
	else{
		return "Unknown Potion";
	}
}
//give player attack(negative attack)
void WoundAttack::use(Player* player){
	player->giveAttack(value);
    seen = true;
	removePotion();
}
