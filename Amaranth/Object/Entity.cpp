#include "../Object/Headers/Entity.h"

Entity::Entity()
	: coordinate(0, 0), length(1, 1), velocity(0.0f),
	textureID(0), dt(0.0f), healthPoints(1.0f)
{ }

Entity::Entity(glm::vec2 coords, glm::vec2 len, glm::vec2 vel,
	GLuint texID)
	: coordinate(coords), length(len), velocity(vel), textureID(texID), dt(0.0f) , healthPoints(1.0f)
{ }



