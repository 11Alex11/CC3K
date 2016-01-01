#include "treasure.h"
#include "textdisplay.h"
#include "player.h"
#include "floor.h"
#include <iostream>
Treasure::Treasure(int x, int y,int value,Floor * floor):Entity("G",x,y,floor),value(value){
	
}

void Treasure::draw(TextDisplay& td){
	td.notify(x,y,'G');
}

int Treasure::getValue(){
	return value;
}
//return true if given a player(player can walk on it), otherwise false
bool Treasure::canCollideWith(const Entity* entity)
{
	const Player* player = dynamic_cast<const Player*>(entity);
	if (player == NULL) return true;
	return false;
}

//called by player(visitor pattern), give the value of gold to the player
//as well as remove the treasure from the floor
void Treasure::use(Player& player){
	player.giveGold(value);
	Entity* remove = floor->grid[x][y].at(1);
	floor->grid[x][y].erase(floor->grid[x][y].begin()+1);
	delete remove;
}
