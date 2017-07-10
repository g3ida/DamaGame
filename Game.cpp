#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

#include "Game.h"
#include "Log.h"

#include "Shapes.h"


void
Game::init()
{
    damier.reset();
}


void
Game::draw()
{
    LOG("display\n");

    glClearColor(0.3f,0.7f,0.7f,0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
    glLineWidth(2);

    damier.draw(0, 0);

    glPopMatrix();

    glFlush();
	glutSwapBuffers();
}

void
Game::update()
{
    LOG("update\n");
}

void
Game::resize(int w, int h)
{
    LOG("resize", w, "x", h, "\n");
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
    // Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	//Maybe i have to take care of the scaling h < w
	if (w > h)
    {
        gluOrtho2D(-1 * ratio, 1 * ratio, -1, 1);
    }
    else
    {
        gluOrtho2D(-1, 1, -1 / ratio, 1 / ratio);
    }
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void
Game::onKey(unsigned char key, int x, int y)
{
    LOG("key\n");
}
