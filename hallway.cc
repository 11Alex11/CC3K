#include "hallway.h"
#include "textdisplay.h"
#include "player.h"
Hallway::Hallway( int x, int y,Floor* floor):Entity("#",x,y,floor){
 
}
void Hallway::draw(TextDisplay& td){
	td.notify(x,y,'#');
}
//override entity method, return false(so player can walk on it)
bool Hallway::canCollideWith(const Entity* entity)
{
  const Player* player = dynamic_cast<const Player*>(entity);
  if (player == NULL) return true;
  return false;
}