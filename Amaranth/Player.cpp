#include "Player.h"

Player::Player()
{
	speed = 0.333;
}

void Player::moveRight()
{
	setCoordX(getCoordX() + (speed*AR));
}

void Player::moveLeft()
{
	setCoordX(getCoordX() - (speed*AR));
}
