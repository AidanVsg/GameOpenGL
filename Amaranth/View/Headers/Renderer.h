#include "../Object/Headers/Entity.h"
#include "../Object/Headers/Player.h"
#include "../Object/Headers/World.h"

#pragma once
class Renderer
{
private:
	Player player;
public:
	void display(Entity entity);						//called in winmain to draw everything to the screen
	void reshape(int width, int height, 
				int currentWidth, int currentHeight);	//called when the window is resized
	void init();										//called in winmain when the program starts.
	void update();										//called in winmain to update variables
	void drawEntity(Entity _entity);					//draws an Entity (Player, NPC)
};

