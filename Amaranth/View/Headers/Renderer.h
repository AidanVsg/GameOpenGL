#include "../Object/Headers/Entity.h"
#include "../Object/Headers/Player.h"
#include "../Object/Headers/World.h"
#include <windows.h>		// Header file for Windows
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>			// Header file for the GLu32 Library

#pragma once

class Renderer
{
private:
	Player player;
	
public:
	void display(Player p, World world);						//called in winmain to draw everything to the screen
	void reshape(int width, int height, 
				int currentWidth, int currentHeight);	//called when the window is resized
	void init();										//called in winmain when the program starts.
	void update();										//called in winmain to update variables
	void drawEntity(Entity entity);					//draws an Entity (Player, NPC)

};
