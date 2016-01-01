#ifndef _POTION_H_
#define _POTION_H_
#include "entity.h"
class Player;
class Floor;
class TextDisplay;
class Potion:public Entity{
protected:
	int value;
	void removePotion();
public:
	Potion(int x, int y, int value,std::string name,Floor* floor);
	virtual void draw(TextDisplay &td);
	virtual void use(Player* player)=0;
};




#endif