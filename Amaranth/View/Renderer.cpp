#include "../View/Headers/Renderer.h"

void Renderer::display(Player p, World world)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	//if (LeftPressed)
	//	glColor3f(1.0, 0.0, 0.0);
	//else
	//	glColor3f(1.0, 1.0, 1.0);

	//World _world; //TODO learn how to put all objects in a list (possibly VECTOR structure)

	//_world.addEntity(_player); //TODO objects in list
	//player.setCoordX(0);
	drawEntity(p, p.getCoords());

	for (Entity e : world.getEntities())
	{
		drawEntity(e, e.getCoords());
	}
	

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
	//spin += speed;
	//if (spin > 360)
	//spin = 0;
}

void Renderer::drawEntity(Entity entity, std::vector<std::pair<int,int>> coordset)
{
	glPushMatrix();
		glTranslatef(entity.getCoordX(), entity.getCoordY(), 0.0);
		glBegin(GL_POLYGON);
		for (auto coords : coordset) {
			int x = coords.first;
			int y = coords.second;

			glVertex2f(x, y);

		}
			

		glEnd();
	glPopMatrix();


}

