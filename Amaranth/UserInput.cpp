#include "UserInput.h"
#include <windows.h>
#include <iostream>

UserInput::UserInput()
{
}

void UserInput::processKeys()
{
	if (keys[VK_UP]) {
		//speed += 0.0001f;
		//std::cout << "up: " << speed << std::endl;
	}
	if (keys[VK_DOWN]) {
		//speed -= 0.0001f;
		//std::cout << "down: " << speed << std::endl;
	}
	if (keys[VK_LEFT]) {
		//pos -= 0.5f;
		//std::cout << "left: " << pos << std::endl;

		//Player.mvLeft();
	}
	if (keys[VK_RIGHT]) {
		//pos += 0.5f;
		//std::cout << "right: " << pos << std::endl;

		//Player.mvRight();
	}
}
