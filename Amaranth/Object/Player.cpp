#include "../Object/Headers/Player.h"
#include <iostream>

Player::Player() : Entity(), jumpHeight(0.0f), jstate(JumpState::FALLING), collision(Direction::NONE, Direction::NONE), initialVelocity(velocity), seconds_on_ground(0)
{ }

Player::Player(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, Texture tex,
	float jumpH)
	: Entity(coords, len, vel, tex), jstate(JumpState::FALLING), jumpHeight(jumpH), initialVelocity(velocity), collision(Direction::NONE, Direction::NONE), seconds_on_ground(0)
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
	}
	if (keys[VK_DOWN] || keys[0x53])
	{

	}
	if (keys[VK_LEFT] || keys[0x41]) 
	{
		moveLeft();
	}
	if (keys[VK_RIGHT] || keys[0x44])
	{
		moveRight();
	}
}

bool Player::checkCollision(Entity* &e)
{
	bool on_x = coordinate.x + length.x >= e->GetCoordinate().x && e->GetCoordinate().x + e->GetLength().x >= coordinate.x;
	bool on_y = coordinate.y + length.y >= e->GetCoordinate().y && e->GetCoordinate().y + e->GetLength().y >= coordinate.y;

	return on_x && on_y;
}

void Player::resetCollisions()
{
	collision = Player::CollisionSides(Player::Direction::NONE, Player::Direction::NONE);
}

void Player::collisionSide(Entity* &e)
{
	glm::vec2 pHalf(length.x / 2, length.y / 2);
	glm::vec2 pCenter(coordinate.x + pHalf.x, coordinate.y + pHalf.y);

	glm::vec2 eHalf(e->GetLength().x / 2, e->GetLength().y / 2);
	glm::vec2 eCenter(e->GetCoordinate().x + eHalf.x, e->GetCoordinate().y + eHalf.y);

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

	switch (best_match)
	{
	case 0:
		if(!e->GetN_up())
			collision.second = (Direction)best_match;
		break; 
	case 2:
		if (!e->GetN_down())
			collision.second = (Direction)best_match;
		break;
	case 1:
		if (!e->GetN_right())
			collision.first = (Direction)best_match;
		break;
	case 3:
		if (!e->GetN_left())
			collision.first = (Direction)best_match;
		break;
	}
}

void Player::moveRight(){ if (collision.first != Direction::LEFT) coordinate.x += velocity.x*dt;}

void Player::moveLeft(){ if (collision.first != Direction::RIGHT) coordinate.x -= velocity.x*dt;}

void Player::jump()
{

	if (jstate == JumpState::ON_GROUND)
	{
		initialCoordY = coordinate.y;
		//this->state = JumpState::JUMPING;
		jstate = JUMPING;

	}
}

void Player::checkJumpState(float dt)
{
	this->dt = dt;
	if (velocity.y > 80.0f) velocity.y = 80.0f;
	if (dt > 0.15f) dt = 0.15f;
		

	float g = -9.81;
	float v_old, c_old, fc;
	double ndt;

	if (collision.second == UP)
	{
		initialCoordY = coordinate.y;
		//velocity.y = initialVelocity.y;
	}

	v_old = velocity.y;
	c_old = coordinate.y;

	switch (jstate)
	{
	case FALLING:

		velocity.y = v_old + g*dt;
		coordinate.y = c_old + ((v_old + velocity.y) / 2)*dt; // Use improved Euler Integration
		if (coordinate.y < initialCoordY)
		{
			if (collision.second == NONE)
			{
				jstate == FALLING;
			}
			else {
				jstate = ON_GROUND;
				velocity.y = -velocity.y;
			}
		}
		break;
	case JUMPING:

		//fc = (jumpHeight - coordinate.y) / jumpHeight; // Find point of collision
		//ndt = fc*dt;			 // Calculate remaining timestep
		velocity.y = v_old + g*dt;  // Reintegrate
		if (velocity.y < 0) 
			jstate = FALLING;
		if (collision.second == DOWN)
		{
			jstate = FALLING;
			velocity.y = -velocity.y;
			break;
		}
		coordinate.y = coordinate.y + (((v_old + velocity.y) / 1.4)*dt);
		if (coordinate.y > initialCoordY + jumpHeight)
		{
			jstate = FALLING;
			velocity.y = 15.0f;
		}
			
		break;
	case ON_GROUND:
		if (collision.second == UP) { //TODO check if on ground for more than second, then change velocity
			if (seconds_on_ground > 0.5)
			{
				velocity.y = initialVelocity.y;
				seconds_on_ground = 0.0f;
				break;
			}
			seconds_on_ground += dt;
			break;
		}
		else
		{
			jstate = FALLING;
			velocity.y = initialVelocity.y;
			break;
		}

	}
}


