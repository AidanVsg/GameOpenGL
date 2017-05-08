#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "../Object/Headers/Entity.h"
#include "windows.h"
#include <iostream>

class Player : public Entity {
private:
	float initialCoordY;
public:	
	bool keys[256];

	enum JumpState{
		ON_GROUND,
		JUMPING,
		FALLING
	};
	JumpState state;
	enum Collision{
		COLLIDING,
		NO_COLLISION
	};
	Collision coll;
	enum LastCall {
		RIGHT,
		LEFT,
		JUMP,
		NONE
	};
	LastCall lcall;
	
	void processKeys();
	Player();
	void moveRight();
	void moveLeft();
	void jump();
	void checkJumpState();
};

#endif  //_PLAYER_H
