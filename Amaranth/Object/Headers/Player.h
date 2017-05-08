#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "../Object/Headers/Entity.h"
#include "windows.h"
#include <iostream>

class Player : public Entity {
private:
	float initialCoordY;
	bool onFloor;
public:	
	bool keys[256];

	enum JumpState{
		ON_GROUND,
		JUMPING,
		FALLING
	};
	JumpState state;
	enum Collision{
		TOP,
		BOTTOM,
		RIGHT,
		LEFT,
		NONE
	};
	Collision coll;

	void processKeys();
	Player();
	void moveRight();
	void moveLeft();
	void jump();
	void checkJumpState();
	void checkFloor();
};

#endif  //_PLAYER_H
