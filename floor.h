#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <string>
#include <vector>
#include "entity.h"

// Floor is a dumb container, allowing Entities to interact with each
// other, pretty much just a wrapper for the grid.
class Floor
{
private:
	int playerX,playerY;
	int stairsX,stairsY;
	std::string input;
	const int floorHeight;
	const int floorWidth;
public:
	std::vector<Entity* > ** grid;
	Floor(std::string input="random");
	void init(int offset);
	void insertEntity(int destx, int desty, Entity* entity);
	void removeEntity(int x, int y, Entity* entity);
	void moveEntity(int x, int y, int destx, int desty, Entity* entity);
	int getHeight() const;
	int getWidth() const;
	int getPlayerX();
	int getPlayerY();
	int getStairsX();
	int getStairsY();
	~Floor();
};


#endif
