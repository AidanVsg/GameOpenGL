#if !defined(_WORLD_H)
#define _WORLD_H

#include "../Object/Headers/Entity.h"
#include <vector>

class World {
private:
    int numberOfEntities = 0;
	std::vector<Entity> entities;
public:
	World();
	Entity getEntity(int x);
	void addEntity(Entity entity);
};




#endif  //_WORLD_H
