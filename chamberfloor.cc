#include "chamberfloor.h"
#include "textdisplay.h"
 
ChamberFloor::ChamberFloor( int x, int y,Floor* floor):Entity(".",x,y,floor){

}
void ChamberFloor::draw(TextDisplay& td){
	td.notify(x,y,'.');
}

bool ChamberFloor::canCollideWith(const Entity* entity)
{
  return false;
}
