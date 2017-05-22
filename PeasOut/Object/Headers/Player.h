#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "../Object/Headers/Entity.h"
#include <windows.h>

class Player : public Entity {
public:
	Player();
	Player(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, GLuint texID, float jumpH, int sc);
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

	enum Moving {
		MLEFT,
		MRIGHT,
		OTHER
	};

	typedef Direction Horizontal;//For horizontal collision (Up or Down)
	typedef Direction Vertical;//For vertical collision (Left or Right)

	typedef std::pair<Horizontal, Vertical> CollisionSides;

	GET(Texture, t, Textures)
	SET(Texture, t, Textures)
	GET(int, score, Score)
	SET(int, score, Score)

	bool keys[256];

	bool checkCollision(Entity &second);
	void collisionSide(Entity &e);
	void resetCollisions(), processKeys(), moveRight(), moveLeft(), jump(), checkJumpState(float dt);
private:
	Texture t;
	CollisionSides collision;
	JumpState jstate;
	Moving moving;
	float initialCoordY, jumpHeight, seconds_on_ground;
	int score;
	glm::vec2 initialVelocity;
};



#endif  //_PLAYER_H


