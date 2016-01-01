#include "dragonhoard.h"
#include "textdisplay.h"
#include "player.h"
#include "floor.h"
#include <iostream>

DragonHoard::DragonHoard(int x, int y,int value,Floor * floor):Treasure(x,y,value,floor){
	dead=false;
}

//sets dead to true, allow player to now walk on this
void DragonHoard::setDragonDead(){
	dead=true;
}
//return true(player can walk on it) if dragon is dead and the entity
//given is a player
bool DragonHoard::canCollideWith(const Entity* entity)
{
  const Player* player = dynamic_cast<const Player*>(entity);
  if (dead==false|| player==NULL) return true;
  return false;
}

