#include "Entity.h"

Entity::Entity()
{
}

void Entity::setTexture(Texture _texture)
{
}

void Entity::setCoordX(float x)
{
	Entity::coordX = x;
}

void Entity::setCoordY(float y)
{
	Entity::coordY = y;
}

void Entity::setHitPoints(float hp)
{
	Entity::hitPoints = hp;
}

float Entity::getCoordX()
{
	return coordX;
}

float Entity::getCoordY()
{
	return coordY;
}

float Entity::getHitPoints()
{
	return hitPoints;
}

Texture Entity::getTexture()
{
	return Texture();
}

