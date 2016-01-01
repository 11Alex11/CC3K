#include "phoenix.h"
#include "enemy.h"
#include "textdisplay.h"
#include <string>
#include "floor.h"
using namespace std;
Phoenix::Phoenix(int x, int y,Floor* floor):Enemy(50,35,20,x,y,"X",floor){};


void Phoenix::draw(TextDisplay& td){
	td.notify(x,y,'X');
}

