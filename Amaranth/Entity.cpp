#include "Entity.h"

Entity::Entity()
{
}

void Entity::setAR(float ar) {
	this->AR = ar;
}

void Entity::setTexture(Texture _texture)
{
}

void Entity::setCoordX(float x)
{
	this->coordX = x;
}

void Entity::setCoordY(float y)
{
	this->coordY = y;
}

void Entity::setHitPoints(float hp)
{
	this->hitPoints = hp;
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

