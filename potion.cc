#include "potion.h"
#include "floor.h"
#include "textdisplay.h"
Potion::Potion(int x,int y,int value,std::string name,Floor* floor)
  :value(value), Entity(name,x,y,floor){}

void Potion::draw(TextDisplay& td){
	td.notify(x,y,'P');
}

void Potion::removePotion(){
	Entity* remove = floor->grid[x][y].at(0);
	floor->grid[x][y].erase(floor->grid[x][y].begin());
	delete remove;
}