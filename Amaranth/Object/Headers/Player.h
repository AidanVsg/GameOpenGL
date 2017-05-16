#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "../Object/Headers/Entity.h"
#include <windows.h>

class Player : public Entity {
public:
	Player();
	Player(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, Texture tex, float jumpH);
	enum JumpState {
		ON_GROUND,
		JUMPING,
		FALLING
	};

	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE
	};

	Direction direction;
	JumpState state;

	bool keys[256];

	bool checkCollision(Entity &second);
	Direction collisionSide(Entity &e);
	void resetCollisions(), processKeys(), moveRight(), moveLeft(), jump(), checkJumpState(float dt), checkFloor();
private:
	float initialCoordY, jumpHeight;
};

#endif  //_PLAYER_H
