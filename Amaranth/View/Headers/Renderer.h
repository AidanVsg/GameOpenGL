#if !defined(_RENDERER_H)
#define _RENDERER_H

#include "../Object/Headers/Entity.h"
#include "../Object/Headers/Player.h"
#include "../Object/Headers/World.h"
#include <windows.h>		// Header file for Windows
//#include <gl\gl.h>			// Header file for the OpenGL32 Library
//#include <gl\glu.h>			// Header file for the GLu32 Library
#include "../glew/include/GL/glew.h"

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"

#pragma once

class Renderer
{
private:
	Player player;
	
public:
	void display(Player p, World world);						//called in winmain to draw everything to the screen
	void reshape(int width, int height);	//called when the window is resized
	void reshape(int width, int height, Player p);
	void init();										//called in winmain when the program starts.									//called in winmain to update variables
	void drawEntity(Entity entity);			//draws an Entity (Player, NPC)

};
#endif
