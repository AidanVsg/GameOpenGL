
#include "../View/Headers/Renderer.h"

Renderer::Renderer(float ratio) : aspectRatio(ratio)
{}

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

void Renderer::displayMenu(std::vector<Entity*> entities)
{
	float w = screen_width / virtual_width;
	float h = screen_height / virtual_height;
	const float c = 200.0f;
	GLdouble camX = 0;
	GLdouble camXWidth = 0 + c * w;
	GLdouble camY = 0;
	GLdouble camYHeight = 0 + c *h;


	glViewport(0, 0, screen_width, screen_height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(camX, camXWidth, camY, camYHeight);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	for (Entity *e : entities)
	{
		drawEntity(e);
	}

	glFlush();
}

std::pair<Renderer::X, Renderer::Y> Renderer::reshape(int width, int height, Player *p)
{
	float arNow = (float) width / height;

	float w = screen_width / virtual_width;
	float h = screen_height / virtual_height;
	const float c = 200.0f;
	GLdouble camX = p->GetCoordinate().x - c * w;
	GLdouble camXWidth = p->GetCoordinate().x + c * w;
	GLdouble camY = p->GetCoordinate().y - c * h;
	GLdouble camYHeight = p->GetCoordinate().y + c *h;



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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, entity->GetTextureID());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glPushMatrix();
		glTranslatef(entity->GetCoordinate().x, entity->GetCoordinate().y, 0.0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0f, entity->GetLength().y);
		glTexCoord2f(1.0, 1.0); glVertex2f(entity->GetLength().x, entity->GetLength().y);
		glTexCoord2f(1.0, 0.0); glVertex2f(entity->GetLength().x, 0.0f);


		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}


