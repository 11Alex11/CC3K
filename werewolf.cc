#include "werewolf.h"
#include "enemy.h"
#include "textdisplay.h"
#include <string>
#include "floor.h"

using namespace std;
Werewolf::Werewolf(int x, int y,Floor* floor):Enemy(120,30,5,x,y,"W",floor){};


void Werewolf::draw(TextDisplay& td){
	td.notify(x,y,'W');
}

