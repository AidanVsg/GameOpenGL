#include "../Object/Headers/World.h"
#include <iostream>

World::World() {
	entities[0] = Entity();
}

Entity World::getEntity(int x)
{
	if (x < 0 || x > numberOfEntities) {
		std::cout << "Entity" << x << "does not exist" << std::endl;
		return entities[0];
	}
	else {
		return entities[x];
	}
	
}

void World::addEntity(Entity _entity)
{
	entities[numberOfEntities] = _entity;
	numberOfEntities++;
}
