
#include "../View/Headers/Renderer.h"

void Renderer::display(Player *p, std::vector<Entity*> entities)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	drawEntity(p);

	for (Entity *e : entities)
	{
		drawEntity(e);
	}
	

	glFlush();

}
std::pair<Renderer::X, Renderer::Y> Renderer::reshape(int width, int height, Player *p)
{
	const float c = 270.0f;
	GLdouble camX = p->GetCoordinate().x - c;
	GLdouble camXWidth = p->GetCoordinate().x + c;
	GLdouble camY = p->GetCoordinate().y - c;
	GLdouble camYHeight = p->GetCoordinate().y + c;

	std::pair<X, Y> cam; cam.first.first = camX; cam.first.second = camXWidth; cam.second.first = camY; cam.second.second = camYHeight;

	glViewport(0, 0, width, height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(camX, camXWidth, camY, camYHeight);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix


	return cam;
}

void Renderer::init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);						//sets the clear colour to black
															//glClear(GL_COLOR_BUFFER_BIT) in the display function
															//will clear the buffer to this colour.
}

void Renderer::drawEntity(Entity *entity)
{
	glPushMatrix();
		glTranslatef(entity->GetCoordinate().x, entity->GetCoordinate().y, 0.0);
		glBegin(GL_POLYGON);

		glVertex2f(0.0f, 0.0f); 
		glVertex2f(0.0f, entity->GetLength().y); 
		glVertex2f(entity->GetLength().x, entity->GetLength().y); 
		glVertex2f(entity->GetLength().x, 0.0f);


		glEnd();
	glPopMatrix();


}


