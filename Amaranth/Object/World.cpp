#include "../Object/Headers/World.h"
#include <iostream>

World::World() {
	entities[0] = Entity();
}

Entity World::getEntity(int x)
{
	if (x < 0 || x > entities.size) {
		std::cout << "Entity" << x << "does not exist" << std::endl;
		return entities[0];
	}
	else {
		return entities[x];
	}
	
}

void World::addEntity(Entity e)
{
	entities.push_back(e);
}
