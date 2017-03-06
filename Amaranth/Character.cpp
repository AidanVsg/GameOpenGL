#include "Character.h"
#include <windows.h>		// Header file for Windows
#include <iostream>
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>	

Character::Character(float pos)
{
	
	//glPushMatrix();
	//	glTranslatef(pos, 0.0, 0.0);
	//	//glTranslatef(-100, -100, 0);
	//	glBegin(GL_POLYGON);
	//		glVertex2f(0, 0);
	//		glVertex2f(0, 150);
	//		glVertex2f(150, 150);
	//		glVertex2f(150, 0);
	//	glEnd();
	//glPopMatrix();
	//draw triangle
	glPushMatrix();
	glTranslatef(pos,0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(0, 0);
			glVertex2f(0, 50);
			glVertex2f(50, 50);
			glVertex2f(50, 0);
		glEnd();


	
	glPopMatrix();
}

