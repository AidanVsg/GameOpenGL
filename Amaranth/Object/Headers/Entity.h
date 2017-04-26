#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "../View/Headers/Texture.h"

class Entity {
public:
	//CONSTRUCTORS
	Entity();
	~Entity();
	//SETTERS
	inline void setAR(float ar);
	inline void setTexture(Texture _texture);
	inline void setCoordX(float x);
	inline void setCoordY(float y);
	inline void setHitPoints(float hp);
	//GETTERS
	inline Texture getTexture();
	inline float getCoordX();
	inline float getCoordY();
	inline float getHitPoints();
protected:
	float speed; //entity speed
	float AR; 
	Texture texture;
	float coordX = 0.0;
	float coordY = 0.0;
	float hitPoints = 0.0;
};

inline void Entity::setAR(float ar) {
	this->AR = ar;
}

inline void Entity::setTexture(Texture _texture)
{
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
	return coordX;
}

inline float Entity::getCoordY()
{
	return coordY;
}

inline float Entity::getHitPoints()
{
	return hitPoints;
}

inline Texture Entity::getTexture()
{
	return Texture();
}



#endif  //_ENTITY_H
