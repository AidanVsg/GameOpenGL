
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

	drawEntity(p);

	for (Entity e : world.getEntities())
	{
		drawEntity(e);
	}
	

	glFlush();

}
void Renderer::reshape(int width, int height, Player p)
{
	const float c = 270.0f;
         // to ensure the mouse coordinates match 
															// we will use these values to set the coordinate system

	glViewport(0, 0, width, height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(p.GetCoordinate().x - c, p.GetCoordinate().x + c, 
				p.GetCoordinate().y - c, p.GetCoordinate().y + c);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}

void Renderer::reshape(int width, int height)
{
       // to ensure the mouse coordinates match 
															// we will use these values to set the coordinate system
	
	glViewport(0, 0, width, height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(0, width, 0, height);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}

void Renderer::init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);						//sets the clear colour to black
															//glClear(GL_COLOR_BUFFER_BIT) in the display function
															//will clear the buffer to this colour.
}

void Renderer::drawEntity(Entity entity)
{
	glPushMatrix();
		glTranslatef(entity.GetCoordinate().x, entity.GetCoordinate().y, 0.0);
		glBegin(GL_POLYGON);


		//for (auto coords : coordset) {
		//	int x = coords.first;
		//	int y = coords.second;

		//	glVertex2f(x, y);
		//}
		glVertex2f(0.0f, 0.0f); 
		glVertex2f(0.0f, entity.GetLength().y); 
		glVertex2f(entity.GetLength().x, entity.GetLength().y); 
		glVertex2f(entity.GetLength().x, 0.0f);

		//glVertex2f(entity.GetCoordinate().x, entity.GetCoordinate().y);

			

		glEnd();
	glPopMatrix();


}


