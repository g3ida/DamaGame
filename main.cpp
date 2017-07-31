#include "logger/Log.h"
#include "InputQueue.h"
#include "Game.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Glut callbacks

void displayCallback()
{
    Game::getInstance().draw();
}

void reshapeCallback(int w, int h)
{
    InputQueue::Event e;
	e.type = InputQueue::Event::Type::Reshape;
	e.data.reshape = InputQueue::Event::ReshapeData{w, h};
	InputQueue::getInstance().push(e);

    InputQueue::getInstance()._screenW = w;
    InputQueue::getInstance()._screenH = h;

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
    // Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
    gluOrtho2D(0, w, h, 0);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void keyboardCallback(unsigned char key, int x, int y)
{
	InputQueue::Event e;
	e.type = InputQueue::Event::Type::Keyboard;
	e.data.keyboard = InputQueue::Event::KeyboardData{x, y, key};
	InputQueue::getInstance().push(e);
}

void mouseCallback(int button, int state, int x, int y)
{
    InputQueue::getInstance()._mouseX = x;
    InputQueue::getInstance()._mouseY = y;

	InputQueue::Event e;
	e.type = InputQueue::Event::Type::Mouse;
	e.data.mouse = InputQueue::Event::MouseData{button, state, x, y};
	InputQueue::getInstance().push(e);
}

void motionCallback(int x, int y)
{
    InputQueue::getInstance()._mouseX = x;
    InputQueue::getInstance()._mouseY = y;

	InputQueue::Event e;
	e.type = InputQueue::Event::Type::MouseMotion;
	e.data.mouseMotion = InputQueue::Event::MouseMotionData{x, y};
	InputQueue::getInstance().push(e);
}

void passiveMotionCallback(int x, int y)
{
    InputQueue::getInstance()._mouseX = x;
    InputQueue::getInstance()._mouseY = y;

	InputQueue::Event e;
	e.type = InputQueue::Event::Type::MousePassiveMotion;
	e.data.mousePassiveMotion = InputQueue::Event::MousePassiveMotionData{x, y};
	InputQueue::getInstance().push(e);
}

void processSpecialKeysCallback(int key, int x, int y)
{
	InputQueue::Event e;
	e.type = InputQueue::Event::Type::KeyboardSpecial;
	e.data.keyboardSpecial = InputQueue::Event::KeyboardSpecialData{key, x, y};
	InputQueue::getInstance().push(e);
}

using namespace std::literals::chrono_literals;
void idleCallback()
{
    glutPostRedisplay();
    std::this_thread::sleep_for(30ms);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(-1,-1);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Jeu De Dames");

    //Register callbacks.
    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutPassiveMotionFunc(passiveMotionCallback);
    glutSpecialFunc(processSpecialKeysCallback);

    glutIdleFunc(idleCallback);

    //Launch the game thread and detach it.
    std::thread t([](){Game::getInstance()();});
    t.detach();


    glutMainLoop();
    //glutMainLoop();

    return EXIT_SUCCESS;
}
