#include "Entity.h"

#pragma once
class Renderer
{
public:
	Renderer();
	void display();				//called in winmain to draw everything to the screen
	void reshape(int width, int height, int currentWidth, int currentHeight);				//called when the window is resized
	void init();				//called in winmain when the program starts.
	void update();				//called in winmain to update variables
	void drawEntity(Entity _entity);
};

