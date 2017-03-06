#include "Character.h"
#include <windows.h>		// Header file for Windows
#include <iostream>
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>	

Character::Character()
{

}

void Character::setPos(float pos)
{
	x = pos;
}

float Character::getPos()
{
	return
		x;
}

void Character::draw()
{
	glTranslatef(x, 0.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 50);
	glVertex2f(50, 50);
	glVertex2f(50, 0);
	glEnd();
}


