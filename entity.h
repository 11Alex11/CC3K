#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <string>
#include "vector.h"
class Floor;
class TextDisplay;

class Entity{
private:
	std::string name;
protected:
	int x,y;
        Floor* floor;
public: 
	Entity(std::string name,int x, int y,Floor* floor);
	virtual Vector tick();
	virtual std::string getName();
    virtual bool canCollideWith(const Entity* entity);
	virtual std::string observe();
	virtual void draw(TextDisplay& td)=0;
	virtual ~Entity();
};



#endif
