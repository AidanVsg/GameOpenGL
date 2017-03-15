#include "Renderer.h"
#include <windows.h>		// Header file for Windows
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>			// Header file for the GLu32 Library
#include "World.h"
#include "Player.h"

Renderer::Renderer()
{

}

void Renderer::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	//if (LeftPressed)
	//	glColor3f(1.0, 0.0, 0.0);
	//else
	//	glColor3f(1.0, 1.0, 1.0);

	//World _world; //TODO learn how to put all objects in a list (possibly VECTOR structure)
	Player _player;

	//_world.addEntity(_player); //TODO objects in list
	_player.setCoordX(0);
	drawEntity(_player);


	glFlush();
}

void Renderer::reshape(int width, int height, int currentWidth, int currentHeight)
{
	currentWidth = width; currentHeight = height;           // to ensure the mouse coordinates match 
															// we will use these values to set the coordinate system

	glViewport(0, 0, width, height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(0, currentWidth, 0, currentHeight);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}

void Renderer::init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);						//sets the clear colour to black
															//glClear(GL_COLOR_BUFFER_BIT) in the display function
															//will clear the buffer to this colour.
}

void Renderer::update()
{
	//pos += pos;
	//spin += speed;
	//if (spin > 360)
	//spin = 0;
}

void Renderer::drawEntity(Entity _entity)
{
		glTranslatef(_entity.getCoordX(), 0.0, 0.0);

		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, 50);
		glVertex2f(50, 50);
		glVertex2f(50, 0);
		glEnd();

}

