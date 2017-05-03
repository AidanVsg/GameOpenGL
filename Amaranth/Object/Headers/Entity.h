#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "../View/Headers/Texture.h"


class Entity {
public:
	//CONSTRUCTORS
	Entity();
	~Entity();
	//SETTERS
	inline void setWidthAR(float ar);
	inline void setHeightAR(float ar);
	inline void setTexture(Texture texture);
	inline void setCoordX(float x);
	inline void setCoordY(float y);
	inline void setHitPoints(float hp);
	//GETTERS
	inline Texture getTexture();
	inline float getWidthAR();
	inline float getHeightAR();
	inline float getCoordX();
	inline float getCoordY();
	inline float getHitPoints();
protected:
	float speed; //entity speed
	float widthAR; 
	float heightAR;
	Texture texture;
	float coordX;
	float coordY;
	float hitPoints;
};

inline void Entity::setWidthAR(float ar) {
	
	this->widthAR = ar;
}

inline float Entity::getWidthAR() {

	return this->widthAR;
}

inline void Entity::setHeightAR(float ar) {

	this->heightAR = ar;
}

inline float Entity::getHeightAR() {

	return this->heightAR;
}

inline void Entity::setCoordX(float x)
{
	this->coordX = x;
}

inline void Entity::setCoordY(float y)
{
	this->coordY = y;
}

inline void Entity::setHitPoints(float hp)
{
	this->hitPoints = hp;
}

inline float Entity::getCoordX()
{
	return this->coordX;
}

inline float Entity::getCoordY()
{
	return this->coordY;
}

inline float Entity::getHitPoints()
{
	return hitPoints;
}

void Entity::setTexture(Texture texture)
{
	this->texture = texture;
}

Texture Entity::getTexture()
{
	return this->texture;
}


#endif  _ENTITY_H
