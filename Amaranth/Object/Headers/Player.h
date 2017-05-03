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
	void processKeys();

	enum class JumpState;
	JumpState state;
	Player();
	void moveRight();
	void moveLeft();
	void jump();
	void checkJumpState();
};

#endif  _PLAYER_H
