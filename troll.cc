#include "troll.h"
#include "enemy.h"
#include "textdisplay.h"
#include <string>
#include "floor.h"
using namespace std;
Troll::Troll(int x, int y,Floor* floor):Enemy(120,25,15,x,y,"T",floor){};


void Troll::draw(TextDisplay& td){
	td.notify(x,y,'T');
}

