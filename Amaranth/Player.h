#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
	Player();
	void moveRight();
	void moveLeft();
};

#endif  //_PLAYER_H
