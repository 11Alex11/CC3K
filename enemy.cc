#include "enemy.h"
#include <string>
#include "entity.h"
#include "floor.h"
#include <vector>
#include "vector.h"
#include <cstdlib>
#include "player.h"
using namespace std;

Enemy::Enemy( int health,int attack, int defence,int x, int y,string name,Floor* floor)
  :health(health),attack(attack),defence(defence),Entity( name,x,y,floor){}

//either attack the player if in range or call move
Vector Enemy::tick(){
	Player* player= Player::getPlayer();
	if(abs(player->getX()-x)<=1&&abs(player->getY()-y)<=1){
          player->strike(attack,*this);      
	}
	else{
		return move();	
	}
	Vector ret(x,y);
	return ret;
}
//move the enemy in a random direction
Vector Enemy::move(){
	bool found=false;
	//create a vector of strings representing each direction
	std::string dir[8]={"north","south","west","east","northwest","northeast","southwest","southeast"};
	vector<std::string> move;
	for(int i=0; i<8;i++){
			move.push_back(dir[i]);	
	}
	while(!found){
		int random;
		/*Randomly choose a direction, if occupied then remove that 
		  direction from the vector. If all directions are occupied,
		  move.size() will be 0 and the loop will
		  end and no movement will occur*/
		if(move.size()!=0){
			random=rand()%move.size();
			if(move[random]=="north"){
				if(!floor->grid[x][y+1].at(0)->canCollideWith(this)){
					floor->grid[x][y+1].insert(floor->grid[x][y+1].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					y++;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
			else if(move[random]=="south"){
				if(!floor->grid[x][y-1].at(0)->canCollideWith(this)){
					floor->grid[x][y-1].insert(floor->grid[x][y-1].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					--y;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
			else if(move[random]=="east"){
				if(!floor->grid[x+1][y].at(0)->canCollideWith(this)){
					floor->grid[x+1][y].insert(floor->grid[x+1][y].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					++x;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
			else if(move[random]=="west"){
				if(!floor->grid[x-1][y].at(0)->canCollideWith(this)){
					floor->grid[x-1][y].insert(floor->grid[x-1][y].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					--x;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
			else if(move[random]=="northwest"){
				if(!floor->grid[x-1][y+1].at(0)->canCollideWith(this)){
					floor->grid[x-1][y+1].insert(floor->grid[x-1][y+1].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					--x;
					++y;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
			else if(move[random]=="northeast"){
				if(!floor->grid[x+1][y+1].at(0)->canCollideWith(this)){
					floor->grid[x+1][y+1].insert(floor->grid[x+1][y+1].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					++x;
					++y;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
			else if(move[random]=="southeast"){
				if(!floor->grid[x+1][y-1].at(0)->canCollideWith(this)){
					floor->grid[x+1][y-1].insert(floor->grid[x+1][y-1].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					++x;
					--y;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
			else if(move[random]=="southwest"){
				if(!floor->grid[x-1][y-1].at(0)->canCollideWith(this)){
					floor->grid[x-1][y-1].insert(floor->grid[x-1][y-1].begin(),this);
					floor->grid[x][y].erase(floor->grid[x][y].begin());
					--x;
					--y;
					found=true;
				}
				else{
					move.erase(move.begin()+random);
				}
			}
		}
		else{
			found=true;
		}
	}
	Vector pos(x,y);
	return pos;
}


//Damage (defender) = ceiling(100/(100 + Def(defender)))*Atk(Attacker) 
int Enemy::strike(int attackPower){
        // ceiling integer division: ((a + b - 1) / b) 
        int damage = ((attackPower*100 + (100 + defence) - 1) / (100 + defence));
	
	health -= damage;
	int rethealth=health;
	if (health <= 0){
		rethealth=0;
		Player* player=Player::getPlayer();
		player->giveGold(1);
		Entity* remove = floor->grid[x][y].at(0);
		floor->removeEntity(x,y,this);
		delete remove;
	} 
	return rethealth;
}



int Enemy::getHealth(){
	return health;
}

Enemy::~Enemy(){
}
 
