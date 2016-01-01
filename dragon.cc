#include "dragon.h"
#include "enemy.h"
#include "textdisplay.h"
#include <string>
#include "floor.h"
#include "dragonhoard.h"
#include "player.h"
using namespace std;
Dragon::Dragon(int x, int y,DragonHoard* dh,Floor * floor):Enemy(150,20,20,x,y,"D",floor),hoard(dh){};


void Dragon::draw(TextDisplay& td){
	td.notify(x,y,'D');
}

//entity tick override, wont allow movement for the dragon
//aswell as only attacking the player if in range of its guarded gold
Vector Dragon::tick(){
	Player* player= Player::getPlayer();
	if(abs(player->getX()-hoard->x)<=1&&abs(player->getY()-hoard->y)<=1){
          player->strike(attack,*this);        
	}
	Vector pos(x,y);
	return pos;
}
//enemy strike override, when health is <=0, it will allow
//the player to walk on the dragons guarded hoard
int Dragon::strike(int attackPower){
	// ceiling integer division: ((a + b - 1) / b) 
        int damage = ((attackPower*100 + (100 + defence) - 1) / (100 + defence));
	health -= damage;
	int rethealth=health;
	if (health <= 0){
		hoard->setDragonDead();
		rethealth=0;
		Entity* remove = floor->grid[x][y].at(0);
		floor->removeEntity(x,y,this);
		delete remove;
	} 
	return rethealth;
}

void Dragon::setHoard(DragonHoard* dh){
	hoard=dh;
}
