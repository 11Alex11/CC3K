#include <string>
#include <fstream>
#include <iostream>
#include "vector.h"
#include <ctime>
#include <cstdlib>

#include "floor.h"
#include "player.h"
#include "verticalwall.h"
#include "horizontalwall.h"
#include "chamberfloor.h"
#include "hallway.h"
#include "emptywall.h"
#include "doorway.h"

#include "treasure.h"
#include "dragonhoard.h"

#include "stairs.h"

#include "boostdefence.h"
#include "boostattack.h"
#include "poisonhealth.h"
#include "restorehealth.h"
#include "wounddefence.h"
#include "woundattack.h"


#include "dragon.h"
#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "merchant.h"
#include "phoenix.h"
#include "troll.h"

using namespace std;

//Allocate 2d array of vectors that will contain pointers to Entity
Floor::Floor(string input):floorHeight(25),floorWidth(79),input(input){
	grid = new vector<Entity*>* [25];
	for(int i=0;i<25;i++){
		grid[i]=new vector<Entity*>[79];
	}
}

void Floor::init(int offset){
	char myarray[80];
	char c;
	ifstream file;
	//if not given a command line argument, create a random layout
	if(input=="random"){
		file.open("init2.txt");  //read in basic floor layout first
		for(int i =0;i<floorHeight;i++){
            file.getline(myarray,80,'\n');
			for(int j=0;j<floorWidth;j++){
				c=myarray[j];
                if(c=='|'){
                    VerticalWall* wall= new VerticalWall(i,j,this);
					grid[i][j].push_back(wall);
				}
				else if(c=='-'){
                    HorizontalWall* hwall=new HorizontalWall(i,j,this);
					grid[i][j].push_back(hwall);
				}
				else if(c=='.'){
                    ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}
				else if(c==' '){
                    EmptyWall* empty=new EmptyWall(i,j,this);
					grid[i][j].push_back(empty);
				}
				else if(c=='#'){
                    Hallway* hall = new Hallway(i,j,this);
					grid[i][j].push_back(hall);
				}
				else if (c=='+'){
                    Doorway* door = new Doorway(i,j,this);
					grid[i][j].push_back(door);
				}
			}
			c=file.peek();
			if(c=='\n'){
				cin.ignore();
			}
		}
		string filearr[6]={"buffer","ch3.txt","ch4.txt","ch5.txt","ch1.txt","ch2.txt"};
		vector<Vector> chambers[6];
		int num1,num2;
		//init 5 vectors, representing all chamber floor tiles, where each
		// floor tile is represented as an x and y type vector read in from files
		for(int i=0;i<6;i++){
			file.open(filearr[i].c_str());
			while(file >> num1 >> num2){
				Vector vec(num1,num2);
				chambers[i].push_back(vec);
			}
			file.close();
		}
		int numEnemies=20;
		//calculate and place players position and remove position from corresponding
		//chamber so other entities dont overlap
		int whatChamber =rand()%5+1;
		int whatTile=rand()%chambers[whatChamber].size();
		int x=chambers[whatChamber].at(whatTile).getX();
		int y=chambers[whatChamber].at(whatTile).getY();
		//set the floors playerX and playerY variables to the players position
		//so the Game class can access the starting floor position
		playerX=x;
		playerY=y;
        chambers[whatChamber].erase(chambers[whatChamber].begin()+whatTile);
		//calculate and place stairs position and remove position from corresponding
		//chamber so other entities dont overlap
		int whatFloor=rand()%5+1;
		if(whatFloor==whatChamber){  //randomize position again if same chamber as player
			whatFloor+=rand()%4;
			whatFloor= whatFloor%5+1;
		}
		whatTile=rand()%chambers[whatFloor].size();
		x=chambers[whatFloor].at(whatTile).getX();
		y=chambers[whatFloor].at(whatTile).getY();
		Stairs* stairs = new Stairs(x,y,this);
		stairsX=x;
		stairsY=y;
		grid[x][y].insert(grid[x][y].begin(),stairs);
		chambers[whatFloor].erase(chambers[whatFloor].begin()+whatTile);
		//calculate and place potions position and remove position from corresponding
		//chamber so other entities dont overlap
		for(int i=0;i<10;i++){
			int whatPotion=rand()%6+1;
			whatChamber =rand()%5+1;
			whatTile=rand()%chambers[whatChamber].size();
			x=chambers[whatChamber].at(whatTile).getX();
			y=chambers[whatChamber].at(whatTile).getY();

			if(whatPotion==1){
				RestoreHealth* rh = new RestoreHealth(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),rh);
			}
			else if(whatPotion==2){
				PoisonHealth* ph = new PoisonHealth(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),ph);
			}
			else if(whatPotion==3){
				BoostAttack* ba  = new BoostAttack(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),ba);
			}
			else if(whatPotion==4){
				WoundAttack* wa = new WoundAttack(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),wa);
			}
			else if(whatPotion==5){
				BoostDefence* bd = new BoostDefence(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),bd);
			}
			else{
				WoundDefence* wd = new WoundDefence(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),wd);
			}
			chambers[whatChamber].erase(chambers[whatChamber].begin()+whatTile);
		}
		//calculate and place gold(and dragon if dragon hoard is created)
		//position and remove position from corresponding chamber so 
		//other entities dont overlap
		for(int i=0;i<10;i++){
			int whatGold=rand()%8+1;			
			whatChamber =rand()%5+1;
			whatTile=rand()%chambers[whatChamber].size();
			x=chambers[whatChamber].at(whatTile).getX();
			y=chambers[whatChamber].at(whatTile).getY();
			if(whatGold < 6){
				Treasure* treasure = new Treasure(x,y,1,this);
				grid[x][y].insert(grid[x][y].begin(),treasure);
			}
			else if(whatGold < 8){
				Treasure* treasure = new Treasure(x,y,2,this);
				grid[x][y].insert(grid[x][y].begin(),treasure);
			}
			else{
				DragonHoard* treasure = new DragonHoard(x,y,6,this);
				grid[x][y].insert(grid[x][y].begin(),treasure);
				bool find=true;
				//find suitable position to place the dragon
				while(find){
					int n= rand()%3-1;
					int m= rand()%3-1;
					if(grid[x+n][y+m].at(0)->getName()=="."){
							x+=n;
							y+=m;
							find=false;
						}
				}
				//remove the dragons position from the chamber
				for(int i=0;i<chambers[whatChamber].size();i++){
					if(chambers[whatChamber].at(i).getX()==x
						&&chambers[whatChamber].at(i).getY()==y)
						chambers[whatChamber].erase(chambers[whatChamber].begin()+i);
				}
				//create and place the dragon
				if(find==false){
					Dragon* dragon = new Dragon(x,y,treasure,this);
					grid[x][y].insert(grid[x][y].begin(),dragon);
					numEnemies--;
				}
			}
			chambers[whatChamber].erase(chambers[whatChamber].begin()+whatTile);
		}
		//calculate and place enemies position and remove position 
		//from corresponding chamber so other entities dont overlap
		for(int i=0;i<numEnemies;i++){
			int whatEnemy=rand()%18+1;
			whatChamber =rand()%5+1;
			whatTile=rand()%chambers[whatChamber].size();
			x=chambers[whatChamber].at(whatTile).getX();
			y=chambers[whatChamber].at(whatTile).getY();
			if(whatEnemy<5){
				Vampire* were = new Vampire(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),were);
			}
			else if(whatEnemy<8){
				Werewolf* vamp = new Werewolf(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),vamp);
			}
			else if(whatEnemy<13){
				Goblin* gob = new Goblin(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),gob);
			}
			else if(whatEnemy<15){
				Troll* troll = new Troll(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),troll);
			}
			else if(whatEnemy<17){
				Phoenix* pho = new Phoenix(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),pho);
			}
			else{
				Merchant* merch = new Merchant(x,y,this);
				grid[x][y].insert(grid[x][y].begin(),merch);
			}
			chambers[whatChamber].erase(chambers[whatChamber].begin()+whatTile);
		}
	}
	//else, if given a file to use, create a floor based on that
	else{
		file.open(input.c_str());
		for(int i= 0;i<offset;i++){
			file.getline(myarray,80,'\n');
		}
		for(int i =0;i<floorHeight;i++){
			file.getline(myarray,80,'\n');
			for(int j=0;j<floorWidth;j++){
				c=myarray[j];
				if(c=='|'){
					VerticalWall* wall= new VerticalWall(i,j,this);
					grid[i][j].push_back(wall);
				}
				else if(c=='-'){
					HorizontalWall* hwall=new HorizontalWall(i,j,this);
					grid[i][j].push_back(hwall);
				}
				else if(c=='.'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}
				else if(c==' '){
					EmptyWall* empty=new EmptyWall(i,j,this);
					grid[i][j].push_back(empty);
				}
				else if(c=='#'){
					Hallway* hall = new Hallway(i,j,this);
					grid[i][j].push_back(hall);
				}
				else if (c=='+'){
					Doorway* door = new Doorway(i,j,this);
					grid[i][j].push_back(door);
				}
				else if(c=='\\'){
					Stairs* stairs = new Stairs(i,j,this);
					grid[i][j].push_back(stairs);
					stairsX=i;
					stairsY=j;
				}
				else if(c=='@'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
					playerX=i;
					playerY=j;
				}				
				else if(c=='9'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					DragonHoard* dh = new DragonHoard(i,j,6,this);
					grid[i][j].push_back(dh);
					grid[i][j].push_back(chamber);
				}
				else if(c=='D'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					Dragon* dragon = new Dragon(i,j,NULL,this);
					grid[i][j].push_back(dragon);
					grid[i][j].push_back(chamber);
				}
				else if(c=='8'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					Treasure* treasure = new Treasure(i,j,4,this);
					grid[i][j].push_back(treasure);
					grid[i][j].push_back(chamber);			
				}
				else if(c=='7'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					Treasure* treasure = new Treasure(i,j,2,this);
					grid[i][j].push_back(treasure);
					grid[i][j].push_back(chamber);
				}
				else if(c=='6'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					Treasure* treasure = new Treasure(i,j,1,this);
					grid[i][j].push_back(treasure);
					grid[i][j].push_back(chamber);
				}
				else if (c=='5'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					WoundDefence* wd = new WoundDefence(i,j,this);
					grid[i][j].push_back(wd);
					grid[i][j].push_back(chamber);
				}
				else if (c=='4'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					WoundAttack* wa = new WoundAttack(i,j,this);
					grid[i][j].push_back(wa);
					grid[i][j].push_back(chamber);
				}
				else if (c=='3'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					PoisonHealth* ph = new PoisonHealth(i,j,this);
					grid[i][j].push_back(ph);
					grid[i][j].push_back(chamber);
				}
				else if (c=='2'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					BoostDefence* bd = new BoostDefence(i,j,this);
					grid[i][j].push_back(bd);
					grid[i][j].push_back(chamber);
				}
				else if (c=='1'){
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					BoostAttack* ba = new BoostAttack(i,j,this);
					grid[i][j].push_back(ba);
					grid[i][j].push_back(chamber);
				}
				else if(c=='0'){
					RestoreHealth* rh= new RestoreHealth(i,j,this);
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(rh);
					grid[i][j].push_back(chamber);
				}
				else if(c=='V'){
					Vampire* vamp = new Vampire(i,j,this);
					grid[i][j].push_back(vamp);
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}
				else if(c=='W'){
					Werewolf* were = new Werewolf(i,j,this);
					grid[i][j].push_back(were);
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}
				else if(c=='N'){
					Goblin* goblin= new Goblin(i,j,this);
					grid[i][j].push_back(goblin);
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}
				else if(c=='M'){
					Merchant* merchant=new Merchant(i,j,this);
					grid[i][j].push_back(merchant);
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}
				else if(c=='X'){
					Phoenix* phoenix = new Phoenix(i,j,this);
					grid[i][j].push_back(phoenix);
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}
				else if(c=='T'){
					Troll* troll = new Troll(i,j,this);
					grid[i][j].push_back(troll);
					ChamberFloor* chamber=new ChamberFloor(i,j,this);
					grid[i][j].push_back(chamber);
				}	
			}
			
			
		}
	
		//this will link any created dragons to their dragon hoards
		for(int i=0;i<floorHeight;i++){
				for(int j=0; j<floorWidth;j++){
					Dragon* dragon = dynamic_cast<Dragon*>(grid[i][j].at(0));
					if(dragon!=NULL){
						for(int n =-1;n<=1;n++){
							for(int m=-1;m<=1;m++){
								DragonHoard* hoard = dynamic_cast<DragonHoard*>(grid[i+n][j+m].at(0));
								if(hoard!=NULL){
									dragon->setHoard(hoard);
								}
							}
						}	
					}
				}
			}
	}
}
//insert an entity at a given position on the floor
void Floor::insertEntity(int destx, int desty, Entity* entity)
{
  grid[destx][desty].insert(grid[destx][desty].begin(), entity);

}

//remove an entity at a given position
void Floor::removeEntity(int x, int y, Entity* entity)
{
  for (int i = 0; i < grid[x][y].size(); i++)
    {
      if (entity == grid[x][y][i])
        {
          grid[x][y].erase(grid[x][y].begin() + i);
		  break;
        }
    }
}
//move an entity to a given position
void Floor::moveEntity(int x, int y, int destx, int desty, Entity* entity)
{
  removeEntity(x, y, entity);
  insertEntity(destx, desty, entity);
}

int Floor::getHeight() const
{
  return floorHeight;
}

int Floor::getWidth() const
{
  return floorWidth;
}

int Floor::getPlayerX(){
	return playerX;
}

int Floor::getPlayerY(){
	return playerY;
}

int Floor::getStairsX(){
	return stairsX;
}

int Floor::getStairsY(){
	return stairsY;
}
//delete all entities contained within the vectors of the 2d array
Floor::~Floor(){
	for(int i=0;i<floorHeight;i++){
		for(int j=0;j<floorWidth;j++){
			while(grid[i][j].size()!=0){
				Entity* remove=grid[i][j].back();
				grid[i][j].pop_back();
				delete remove;
			}
		}
	}
	for(int i = 0;i<floorHeight;i++){
		delete [] grid[i];
	}
	delete [] grid;
}
