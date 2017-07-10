#include "Game.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


//Instance globale du jeu
Game MY_GAME;

//Glut callbacks
static void display()
{
    MY_GAME.draw();
}

static void idle()
{
    MY_GAME.update();
    MY_GAME.draw();
}

static void reshape(int w, int h)
{
    MY_GAME.resize(w, h);
}

static void keyboard(unsigned char key, int x, int y)
{
    MY_GAME.onKey(key, x, y);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(-1,-1);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Jeu De Dames");

    //Register callbacks
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    MY_GAME.init();
    glutMainLoop();

    return EXIT_SUCCESS;
}
