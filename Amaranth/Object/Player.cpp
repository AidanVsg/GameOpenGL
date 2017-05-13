#include "../Object/Headers/Player.h"
#include <iostream>

Player::Player() : Entity(), jumpHeight(0.0f), state(JumpState::FALLING), direction(Direction::NONE)
{ }
//this->wAR = 1;
//this->hAR = 1;
//this->coordX = 0.0f;
//this->coordY = 10.0f;
//this->hitPoints = 0.0f;
//this->state = JumpState::ON_GROUND;

//this->speed = 0.45; //TODO add momentum
//this->jumpHeight = 150;

//this->coordset.push_back({ 0,0 });
//this->coordset.push_back({ 0,50 });
//this->coordset.push_back({ 50,50 });
//this->coordset.push_back({ 50,0 });


Player::Player(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, Texture tex,
	float jumpH)
	: Entity(coords, len, vel, tex), state(JumpState::FALLING), direction(Direction::NONE), jumpHeight(jumpH)
{ }

void Player::processKeys()
{
	if (keys[VK_UP] || keys[0x57]) {

		jump();
		/*std::cout << "up: " << getCoordY() << std::endl;*/

	}
	if (keys[VK_DOWN] || keys[0x53]) {

		//TODO crouch/go down
	}
	if (keys[VK_LEFT] || keys[0x41]) {

		moveLeft();
		/*std::cout << "left: " << Get_x() << std::endl;
		std::cout << "left: " << getW_AR() << std::endl;*/
	}
	if (keys[VK_RIGHT] || keys[0x44]) {

		moveRight();
		std::cout << "ar: " << widthAR << std::endl;
		/*std::cout << "right: " << getCoordX() << std::endl;*/
	}
}

bool Player::checkCollision(Entity &e)
{
	bool on_x = coordinate.x + length.x >= e.GetCoordinate().x && e.GetCoordinate().x + e.GetLength().x >= coordinate.x;
	bool on_y = coordinate.y + length.y >= e.GetCoordinate().y && e.GetCoordinate().y + e.GetLength().y >= coordinate.y;

	return on_x && on_y;
}

void Player::resetCollisions()
{
	direction = Direction::NONE;
}

Player::Direction Player::collisionSide(Entity &e)
{
	glm::vec2 pHalf(length.x / 2, length.y / 2);
	glm::vec2 pCenter(coordinate.x + pHalf.x, coordinate.y + pHalf.y);

	glm::vec2 eHalf(e.GetLength().x / 2, e.GetLength().y / 2);
	glm::vec2 eCenter(e.GetCoordinate().x + eHalf.x, e.GetCoordinate().y + eHalf.y);

	glm::vec2 difference = pCenter - eCenter;
	glm::vec2 clamped = glm::clamp(difference, -eHalf, eHalf);
	glm::vec2 closest = eCenter + clamped;

	difference = pCenter - closest;

	glm::vec2 compass[] = {

		glm::vec2(0.0f, 1.0f), // up
		glm::vec2(1.0f, 0.0f), // right
		glm::vec2(0.0f, -1.0f), // down
		glm::vec2(-1.0f, 0.0f) // left
	};
	float max = 0.0f;
	int best_match = 5;
	for (int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(difference), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

void Player::moveRight()
{
	if (direction != Direction::LEFT)
	{
		coordinate.x = coordinate.x + (velocity.x*widthAR);
	}

	//lcall = LastCall::RIGHT;
}

void Player::moveLeft()
{
	if (direction != Direction::RIGHT)
	{
		coordinate.x = coordinate.x - (velocity.x*widthAR);
	}
	//lcall = LastCall::LEFT;
}

void Player::jump()
{
	if (state == JumpState::ON_GROUND)
	{
		initialCoordY = coordinate.y;
		this->state = JumpState::JUMPING;
	}
}

void Player::checkJumpState()
{
	switch (state) {
	case JumpState::ON_GROUND:
		//if (!collidingTop)
		//{
		//	state = JumpState::FALLING;
		//	initialCoordY = 0.0;
		//}
		if (direction != Direction::UP)
		{
			state = JumpState::FALLING;
			break;
		}
		break;
	case JumpState::JUMPING:

		if (coordinate.y < initialCoordY + jumpHeight  && direction != Direction::DOWN)
		{
			coordinate.y = coordinate.y + (velocity.y*heightAR);
		}
		else
		{
			this->state = JumpState::FALLING;
		}

		break;
	case JumpState::FALLING:

		if (coordinate.y > initialCoordY)
		{
			if (direction == Direction::UP)
			{
				this->state = JumpState::ON_GROUND;
			}
			else
			{
				coordinate.y = coordinate.y - (velocity.y*heightAR);
			}

		}
		else
		{
			if (direction != Direction::DOWN)
			{
				initialCoordY = 0.0f;
			}
			else
			{
				this->state = JumpState::ON_GROUND;
			}

		}


		break;
	}

}
