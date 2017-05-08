#include "../Object/Headers/Player.h"



void Player::processKeys()
{
	if (keys[VK_UP] || keys[0x57]) {

		jump();
		std::cout << "up: " << getCoordY() << std::endl;
	}
	if (keys[VK_DOWN] || keys[0x53]) {

		//TODO crouch/go down
	}
	if (keys[VK_LEFT] || keys[0x41]) {

		moveLeft();
		std::cout << "left: " << getCoordX() << std::endl;
		std::cout << "left: " << getW_AR() << std::endl;
	}
	if (keys[VK_RIGHT] || keys[0x44]) {

		moveRight();
		std::cout << "right: " << getCoordX() << std::endl;
	}
}

Player::Player()
{
	this->wAR = 1;
	this->hAR = 1;
	this->coordX = 0.0f;
	this->coordY = 0.0f;
	this->hitPoints = 0.0f;
	this->state = JumpState::ON_GROUND;
	this->coll = Collision::NO_COLLISION;
	this->lcall = LastCall::NONE;
	this->speed = 0.33; //TODO add momentum

	this->coordset.push_back({ 0,0 });
	this->coordset.push_back({ 0,50 });
	this->coordset.push_back({ 50,50 });
	this->coordset.push_back({ 50,0 });
}

void Player::moveRight()
{
	if (coll == Collision::COLLIDING && lcall == LastCall::RIGHT)
	{
		setCoordX(getCoordX());
	}
	else
	{
		setCoordX(getCoordX() + (speed*wAR));
	}

	lcall = LastCall::RIGHT;
}

void Player::moveLeft()
{
	if (coll == Collision::COLLIDING && lcall == LastCall::LEFT)
	{
		setCoordX(getCoordX());
	}
	else
	{
		setCoordX(getCoordX() - (speed*wAR));
	}

	lcall = LastCall::LEFT;
}

void Player::jump()
{
	initialCoordY = getCoordY();
	if (coll == Collision::COLLIDING && lcall == LastCall::JUMP)
	{
		this->state = JumpState::ON_GROUND;
	}
	else
	{
		if (state == JumpState::ON_GROUND) this->state = JumpState::JUMPING;
	}

	lcall = LastCall::JUMP;
}

void Player::checkJumpState()
{
	switch (state) {
	case JumpState::ON_GROUND: break;
	case JumpState::JUMPING: 

		if (getCoordY() < 80) 
		{
			setCoordY(getCoordY() + (speed*hAR));
		}
		else 
		{
			this->state = JumpState::FALLING;
		}

		break;
	case JumpState::FALLING: 

		if (getCoordY() > 0) 
		{
			setCoordY(getCoordY() - (speed*hAR));
		}
		else
		{
			if (getCoordY() < 0) setCoordY(0.0);
			this->state = JumpState::ON_GROUND;
		}

		break;
	}
}
