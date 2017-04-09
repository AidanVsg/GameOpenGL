#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
	float initialCoordY;
public:	
	enum class JumpState;
	JumpState state;
	Player();
	void moveRight();
	void moveLeft();
	void jump();
	void checkJumpState();
};

#endif  //_PLAYER_H
