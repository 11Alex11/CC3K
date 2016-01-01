#include "emptywall.h"
#include "textdisplay.h"
#include "floor.h"
EmptyWall::EmptyWall(int x, int y,Floor* floor):Entity(" ",x,y,floor){

}
void EmptyWall::draw(TextDisplay& td){
	td.notify(x,y,' ');
}