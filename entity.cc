#include "entity.h"
#include <string>
#include "textdisplay.h"
#include "floor.h"
#include "vector.h"
using namespace std;
Entity::Entity(std::string input,int x, int y,Floor* floor):floor(floor), name(input),x(x),y(y){}


string Entity::getName(){
	return name;
}

//all entities return a vector, which allows the Game class
//to skip over entities that have already been ticked
Vector Entity::tick(){
	Vector pos(x,y);
	return pos;
}

//by default, everything can collide with everything,
//some subclasses will override this
bool Entity::canCollideWith(const Entity* entity)
{
  return true;
}

//by default, return an empty string, subclasses can implement
//their own to allow other entities to observer their surroundings,
//which is used to log actions
std::string Entity::observe(){
	return "";
}


Entity::~Entity(){
}