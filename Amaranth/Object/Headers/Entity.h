#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "../View/Headers/Texture.h"
#include <vector>


class Entity {
public:
	//CONSTRUCTORS
	Entity();
	~Entity();
	//SETTERS
	inline void setAR(float wAR, float hAR);
	inline void setTexture(Texture texture);
	inline void setCoordX(float x);
	inline void setCoordY(float y);
	inline void setHitPoints(float hp);
	inline void setCoords(std::vector<std::pair<int, int>> coords);
	//GETTERS
	inline Texture getTexture();
	inline float getW_AR();
	inline float getH_AR();
	inline float getCoordX();
	inline float getCoordY();
	inline float getHitPoints();
	inline std::vector<std::pair<int, int>> getCoords();
protected:
	float speed; //entity speed
	float wAR; 
	float hAR;
	Texture texture;
	float coordX;
	float coordY;
	float hitPoints;
	std::vector<std::pair<int, int>> coordset;
};

inline std::vector<std::pair<int, int>> Entity::getCoords()
{
	return this->coordset;
}

inline void Entity::setCoords(std::vector<std::pair<int, int>> coords)
{
	this->coordset = coords;
}

inline void Entity::setAR(float wAR, float hAR)
{
	
	this->wAR = wAR;
	this->hAR = hAR;
}

inline float Entity::getW_AR() 
{

	return this->wAR;
}

inline float Entity::getH_AR() {

	return this->hAR;
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


#endif  //_ENTITY_H