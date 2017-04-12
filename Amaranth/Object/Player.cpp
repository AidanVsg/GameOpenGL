#include "../Object/Headers/Player.h"

enum class Player::JumpState {
	ON_GROUND,
	JUMPING,
	FALLING
};

Player::Player()
{
	this->state = JumpState::ON_GROUND;
	this->speed = 0.331; //TODO add momentum
}

void Player::moveRight()
{
	setCoordX(getCoordX() + (speed*AR));
}

void Player::moveLeft()
{
	setCoordX(getCoordX() - (speed*AR));
}

void Player::jump()
{
	initialCoordY = getCoordY();
	if(state==JumpState::ON_GROUND) this->state = JumpState::JUMPING;
}

void Player::checkJumpState()
{
	switch (state) {
	case JumpState::ON_GROUND: break;
	case JumpState::JUMPING: 

		if (getCoordY() < 80) 
		{
			setCoordY(getCoordY() + (speed*AR));
		}
		else 
		{
			this->state = JumpState::FALLING;
		}

		break;
	case JumpState::FALLING: 

		if (getCoordY() > 0) 
		{
			setCoordY(getCoordY() - (speed*AR));
		}
		else
		{
			if (getCoordY() < 0) setCoordY(0.0);
			this->state = JumpState::ON_GROUND;
		}

		break;
	}
}
