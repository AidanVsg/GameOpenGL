#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "../Object/Headers/Entity.h"
#include <windows.h>

class Player : public Entity {
public:
	Player();
	Player(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, Texture tex, float jumpH);
	//~Player();

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

	typedef Direction Horizontal;//For horizontal collision (Up or Down)
	typedef Direction Vertical;//For vertical collision (Left or Right)

	typedef std::pair<Horizontal, Vertical> CollisionSides;

	CollisionSides collision;
	Direction direction;
	JumpState state;

	bool keys[256];

	bool checkCollision(Entity &second);
	void collisionSide(Entity &e);
	void resetCollisions(), processKeys(), moveRight(), moveLeft(), jump(), checkJumpState(float dt);
private:


	float initialCoordY, jumpHeight;
	glm::vec2 initialVelocity;
};

#endif  //_PLAYER_H
