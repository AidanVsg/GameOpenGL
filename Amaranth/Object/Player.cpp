#include "../Object/Headers/Player.h"


enum class Player::JumpState {
	ON_GROUND,
	JUMPING,
	FALLING
};


	void Player::processKeys()
	{
		if (keys[VK_UP]) {

			jump();
			std::cout << "up: " << this->getCoordY() << std::endl;
		}
		if (keys[VK_DOWN]) {

			//TODO crouch/go down
		}
		if (keys[VK_LEFT] || keys[0x41]) {

			moveLeft();
			std::cout << "left: " << getCoordX() << std::endl;
			std::cout << "left: " << getWidthAR() << std::endl;
		}
		if (keys[VK_RIGHT] || keys[0x44]) {

			moveRight();
			std::cout << "right: " << this->getCoordX() << std::endl;
		}
	}


Player::Player()
{
	this->widthAR = 1;
	this->heightAR = 1;
	this->coordX = 0.0f;
	this->coordY = 0.0f;
	this->hitPoints = 0.0f;
	this->state = JumpState::ON_GROUND;
	this->speed = 0.33; //TODO add momentum
}

void Player::moveRight()
{
	setCoordX(getCoordX() + (speed*widthAR));
}

void Player::moveLeft()
{
	setCoordX(getCoordX() - (speed*widthAR));
}

void Player::jump()
{
	initialCoordY = getCoordY();
	if(state==JumpState::ON_GROUND) state = JumpState::JUMPING;
}

void Player::checkJumpState()
{
	switch (state) {
	case JumpState::ON_GROUND: break;
	case JumpState::JUMPING: 

		if (getCoordY() < 80) 
		{
			setCoordY(getCoordY() + (speed*heightAR));
		}
		else 
		{
			state = JumpState::FALLING;
		}

		break;
	case JumpState::FALLING: 

		if (this->getCoordY() > 0) 
		{
			setCoordY(getCoordY() - (speed*heightAR));
		}
		else
		{
			if (getCoordY() < 0) setCoordY(0.0);
			state = JumpState::ON_GROUND;
		}

		break;
	}
}
