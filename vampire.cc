#include "vampire.h"
#include "enemy.h"
#include "textdisplay.h"
#include <string>
#include "floor.h"
using namespace std;
Vampire::Vampire(int x, int y,Floor* floor):Enemy(50,25,25,x,y,"V",floor){};


void Vampire::draw(TextDisplay& td){
	td.notify(x,y,'V');
}

