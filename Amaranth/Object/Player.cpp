﻿#include "../Object/Headers/Player.h"
#include <iostream>

Player::Player() : Entity(), jumpHeight(0.0f), state(JumpState::FALLING), direction(Direction::NONE), initialVelocity(velocity)
{ }

Player::Player(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, Texture tex,
	float jumpH)
	: Entity(coords, len, vel, tex), state(JumpState::FALLING), direction(Direction::NONE), jumpHeight(jumpH), initialVelocity(velocity), collision(Direction::NONE, Direction::NONE)
{ }

//Player::~Player()
//{
//	delete(this);
//}

void Player::processKeys()
{
	if (keys[VK_UP] || keys[0x57])
	{
		jump();
		std::cout << "Har: " << heightAR << std::endl;
	}
	if (keys[VK_DOWN] || keys[0x53])
	{

	}
	if (keys[VK_LEFT] || keys[0x41]) 
	{
		moveLeft();
		std::cout << "ar: " << widthAR << std::endl;
		/*std::cout << "left: " << Get_x() << std::endl;
		std::cout << "left: " << getW_AR() << std::endl;*/
	}
	if (keys[VK_RIGHT] || keys[0x44])
	{
		moveRight();
		std::cout << "ar: " << widthAR << std::endl;
	}
}

bool Player::checkCollision(Entity &e)
{
	bool on_x = coordinate.x + length.x >= e.GetCoordinate().x && e.GetCoordinate().x + e.GetLength().x >= coordinate.x;
	bool on_y = coordinate.y + length.y >= e.GetCoordinate().y && e.GetCoordinate().y + e.GetLength().y >= coordinate.y;

	return on_x && on_y;
}

void Player::resetCollisions(){ direction = Direction::NONE;}

void Player::collisionSide(Entity &e)
{
	glm::vec2 pHalf(length.x / 2, length.y / 2);
	glm::vec2 pCenter(coordinate.x + pHalf.x, coordinate.y + pHalf.y);

	glm::vec2 eHalf(e.GetLength().x / 2, e.GetLength().y / 2);
	glm::vec2 eCenter(e.GetCoordinate().x + eHalf.x, e.GetCoordinate().y + eHalf.y);

	glm::vec2 difference = pCenter - eCenter;
	glm::vec2 clamped = glm::clamp(difference, -eHalf, eHalf);
	glm::vec2 closest = eCenter + clamped;

	difference = pCenter - closest;

	glm::vec2 directions[] = {

		glm::vec2(0.0f, 1.0f), // up
		glm::vec2(1.0f, 0.0f), // right
		glm::vec2(0.0f, -1.0f), // down
		glm::vec2(-1.0f, 0.0f) // left
	};
	float max = 0.0f;
	int best_match = 5;
	for (int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(difference), directions[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}

	if (best_match == 1 || best_match == 3)
	{
		collision.first = (Direction)best_match;
	}
	else
	{
		collision.second = (Direction)best_match;
	}
}

void Player::moveRight(){ if (collision.first != Direction::LEFT) coordinate.x += velocity.x*widthAR;}

void Player::moveLeft(){ if (collision.first != Direction::RIGHT) coordinate.x -= velocity.x*widthAR;}

void Player::jump()
{

	if (state == JumpState::ON_GROUND)
	{
		initialCoordY = coordinate.y;
		//this->state = JumpState::JUMPING;
		state = JUMPING;

	}
}

void Player::checkJumpState(float dt)
{


	if (dt > 0.15f) dt = 0.15f;
		

	float g = -9.81; float frac = 0.95;
	float v_old, s_old, fc;
	double ndt;

	if (collision.second == UP)
	{
		initialCoordY = coordinate.y;
		//velocity.y = initialVelocity.y;
	}

	v_old = velocity.y;
	s_old = coordinate.y;

	switch (state)
	{
	case FALLING:

		velocity.y = v_old + g*dt;
		coordinate.y = s_old + ((v_old + velocity.y) / 2.0)*dt; // Use improved Euler Integration
		if (coordinate.y < initialCoordY)
		{
			if (collision.second == NONE)
			{
				state == FALLING;
			}
			else {
				state = ON_GROUND;
				velocity.y = -velocity.y;
			}
		}
		break;
	case JUMPING:

		//fc = (jumpHeight - coordinate.y) / jumpHeight; // Find point of collision
		//ndt = fc*dt;			 // Calculate remaining timestep
		velocity.y = v_old + g*dt;  // Reintegrate
		if (velocity.y < 0) 
			state = FALLING;
		if (collision.second == DOWN)
		{
			state = FALLING;
			velocity.y = -velocity.y;
			break;
		}
		coordinate.y = coordinate.y + (((v_old + velocity.y) / 1.5)*dt);
		if (coordinate.y > initialCoordY + jumpHeight)
		{
			state = FALLING;
			velocity.y = initialVelocity.y;
		}
			
		break;
	case ON_GROUND:
		if (collision.second == UP) {
			velocity.y = initialVelocity.y;
			break;
		}
		else
		{
			state = FALLING;
			velocity.y = initialVelocity.y;
			break;
		}

	}



	/*switch (state) {
	case JumpState::ON_GROUND:

		if (direction != Direction::UP)
		{
			state = JumpState::FALLING;
			break;
		}
		break;
	case JumpState::JUMPING:*/

				
			//coordinate.y = coordinate.y + (velocity.y*heightAR);

	//	break;
	//case JumpState::FALLING:

	//	if (coordinate.y > initialCoordY)
	//	{
	//		if (direction == Direction::UP)
	//		{
	//			this->state = JumpState::ON_GROUND;
	//		}
	//		else
	//		{
	//			
	//			velocity.y = v_old + g*dt;
	//			coordinate.y = s_old + ((v_old + velocity.y) / 2.0)*dt; // Use improved Euler Integration


	//			//coordinate.y = coordinate.y - (velocity.y*heightAR);
	//		}

	//	}
	//	else
	//	{

	//		if (direction != Direction::DOWN)
	//		{
	//			initialCoordY = -15.0f;
	//		}
	//		else
	//		{
	//			this->state = JumpState::ON_GROUND;
	//		}

	//	}


	//	break;
	//}

}
