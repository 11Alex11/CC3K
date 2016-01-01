#include "goblin.h"
#include "enemy.h"
#include "textdisplay.h"
#include <string>
#include "floor.h"
using namespace std;
Goblin::Goblin(int x, int y,Floor* floor):Enemy(70,5,10,x,y,"N",floor){};


void Goblin::draw(TextDisplay& td){
	td.notify(x,y,'N');
}

