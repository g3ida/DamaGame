#include "Game.h"
#include "Log.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Glut callbacks
static void displayCallback()
{
    Game::getInstance().draw();
    glFlush();
	glutSwapBuffers();
}

static void idleCallback()
{
    Game::getInstance().update();
}

static void reshapeCallback(int w, int h)
{
    Game::getInstance().resize(w, h);
}

static void keyboardCallback(unsigned char key, int x, int y)
{
    Game::getInstance().onKey(key, x, y);
	if (key == 27)
    {
        LOG("ESC pressed.. bye :(\n");
        Game::getInstance().quit();
    }
}

static void mouseCallback(int button, int state, int x, int y)
{
    Game::getInstance().onMouse(button, state, x, y);
}

static void processSpecialKeysCallback(int key, int x, int y)
{

}

int x=0;

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(-1,-1);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    Game::getInstance().init("Jeu De Dames");

    //Register callbacks
    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);
    glutIdleFunc(idleCallback);
    glutSpecialFunc(processSpecialKeysCallback);

    glutMainLoop();

    Game::getInstance().quit();

    return EXIT_SUCCESS;
}
