#include "Player.h"

Player::Player()
{
}

void Player::moveRight()
{
	setCoordX(getCoordX() + 0.1);
}

void Player::moveLeft()
{
	setCoordX(getCoordX() - 0.1);
}
