#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "../View/Headers/Texture.h"

class Entity {
public:
	//CONSTRUCTORS
	Entity();
	//SETTERS
	void setAR(float ar);
	void setTexture(Texture _texture);
	void setCoordX(float x);
	void setCoordY(float y);
	void setHitPoints(float hp);
	//GETTERS
	Texture getTexture();
	float getCoordX();
	float getCoordY();
	float getHitPoints();
protected:
	float speed; //entity speed
	float AR; 
	Texture texture;
	float coordX = 0.0;
	float coordY = 0.0;
	float hitPoints = 0.0;
};

#endif  //_ENTITY_H
