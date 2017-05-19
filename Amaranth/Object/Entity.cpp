#include "../Object/Headers/Entity.h"

Entity::Entity()
	: coordinate(0, 0), length(1, 1), velocity(0.0f),
	texture(), dt(0.0f), healthPoints(1.0f)
{ }

Entity::Entity(glm::vec2 coords, glm::vec2 len, glm::vec2 vel,
	Texture tex)
	: coordinate(coords), length(len), velocity(vel), texture(tex), dt(0.0f) , healthPoints(1.0f)
{ }



