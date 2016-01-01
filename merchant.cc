#include "merchant.h"
#include "enemy.h"
#include "textdisplay.h"
#include <string>
#include "floor.h"
#include "player.h"
using namespace std;
bool Merchant::hostile=false;
Merchant::Merchant(int x, int y,Floor* floor):Enemy(30,70,5,x,y,"M",floor){};

void Merchant::resetMerchant(){
	hostile=false;
}

void Merchant::draw(TextDisplay& td){
	td.notify(x,y,'M');
}

//override enemy strike to allow for hostility change
//Damage (defender) = ceiling(100/(100 + Def(defender)))*Atk(Attacker) 
int Merchant::strike(int attackPower){
	// ceiling integer division: ((a + b - 1) / b) 
        int damage = ((attackPower*100 + (100 + defence) - 1) / (100 + defence));
	health -= damage;
	hostile=true;
	int rethealth=health;
	if (health <= 0){
		rethealth=0;
		Entity* remove = floor->grid[x][y].at(0);
		floor->removeEntity(x,y,this);
		Treasure* treasure = new Treasure(x,y,4,floor);
		floor->grid[x][y].insert(floor->grid[x][y].begin(),treasure);
		delete remove;
	} 
	return rethealth;
}

//override entity tick; only attacks if hostile
Vector Merchant::tick(){
	Player* player= Player::getPlayer();
	if(abs(player->getX()-x)<=1&&abs(player->getY()-y)<=1&&hostile==true){
          player->strike(attack,*this);
		  	Vector pos(x,y);
			return pos;
          
	}
	else{
		return move();	
	}
}
