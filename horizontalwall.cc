#include "horizontalwall.h"
#include "textdisplay.h"
#include "floor.h"
HorizontalWall::HorizontalWall(int x, int y,Floor* floor):Entity("-",x,y,floor){

}
void HorizontalWall::draw(TextDisplay& td){
	td.notify(x,y,'-');
}