#include "verticalwall.h"
#include "textdisplay.h"
#include "entity.h"
VerticalWall::VerticalWall(int x, int y,Floor* floor):Entity("|",x,y,floor){

}
void VerticalWall::draw(TextDisplay& td){
  	td.notify(x,y,'|');
}
