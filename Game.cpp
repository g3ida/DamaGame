#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

#include "Game.h"
#include "Log.h"

#include "Shapes.h"
#include <windows.h>

void
Game::init(const std::string& windowTitle)
{
    damier.reset();
    gameWindow = glutCreateWindow("Jeu De Dames");

    player1 = new Player(Damier::WHITE);
    player2 = new Player(Damier::BLACK);
}

void
Game::quit()
{
    glutDestroyWindow(gameWindow);
    gameWindow = 0;

    delete player1;
    delete player2;
}


Game::Game()
{

}

int
Game::getWindow()
{
    return gameWindow;
}


Game&
Game::getInstance()
{
    static Game myGame;
    return myGame;
}


void
Game::draw()
{
//    LOG("display\n");

    glClearColor(0.3f,0.7f,0.7f,0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
    glLineWidth(2);

    damier.draw(damierX, damierY, damierS);

    glPopMatrix();
}

void
Game::update()
{
    //LOG("update\n");
    glutPostRedisplay();

    switch(currentState)
    {
    //player1 turn.
    case TURN_1:
        if(turnFirstPass)
        {
            possiblePlays.clear();
            possiblePlays = damier.getPossibleEats(player1);
            turnFirstPass = false;
        }
        //If there are no jumps.
        if(possiblePlays.empty())
        {
  //          LOG("no jumps");
            //See if there are some available moves.
            possiblePlays = damier.getPossibleMoves(player1);
    //        LOG("got possible moves");
            //If there is nothing to do then the player has lost.
            if(possiblePlays.empty())
            {
      //          LOG("you cannot win");
                currentState = VICTORY_2;
                break;
            }
            //Chose one move among the possible ones.
            auto m = player1->makeMove(damier, possiblePlays);
            LOG(m.first, " white ", m.second, "\n");
            //If it is not a thinking state.
            if(m.first != -1)
            {
                Sleep(1000);
                currentState = TURN_2;
                turnFirstPass = true;
                damier.set(damier.at(m.first), m.second);
                damier.set(Damier::EMPTY, m.first);

            }
        }
        else
        {
            auto m = player1->makeMove(damier, possiblePlays);
        }
        break;
    //player2 turn.
    case TURN_2:
        if(turnFirstPass)
        {
            possiblePlays.clear();
            possiblePlays = damier.getPossibleEats(player2);
            turnFirstPass = false;
        }
        //If there are no jumps.
        if(possiblePlays.empty())
        {
            //See if there are some available moves.
            possiblePlays = damier.getPossibleMoves(player2);

            //If there is nothing to do then the player has lost.
            if(possiblePlays.empty())
            {
                currentState = VICTORY_1;
                break;
            }
            //Chose one move among the possible ones.
            auto m = player2->makeMove(damier, possiblePlays);
            //If it is not a thinking state.
                        LOG(m.first, " white ", m.second, "\n");

            if(m.first != -1)
            {
                Sleep(1000);
                currentState = TURN_1;
                turnFirstPass = true;
                damier.set(damier.at(m.first), m.second);
                damier.set(Damier::EMPTY, m.first);

            }
        }
        else
        {
            auto m = player2->makeMove(damier, possiblePlays);
        }
        break;

    case VICTORY_1:
    case VICTORY_2:
    case DRAW:
        break;
    }
}

void
Game::resize(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
    LOG("resize", w, "x", h, "\n");
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

	damierX = screenWidth / 2;
	damierY = screenHeight / 2;
	damierS = ((w > h)? h : w)*0.75f;
}

void
Game::onKey(unsigned char key, int x, int y)
{
    LOG("key\n");
}

void
Game::onMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(x > damierX - damierS*0.5f && x < damierX +  damierS*0.5f &&
           y > damierY - damierS*0.5f && y < damierY + damierS*0.5f)
        {
            int kx = (x - (int)(damierX - damierS*0.5f)) / ((int)damierS/10);
            int ky = (y - (int)(damierY - damierS*0.5f)) / ((int)damierS/10);
            int k = ky * 10 + kx;
            if(ky % 2 == 0)
            {
                if(k % 2 == 1)
                {
                    LOG(k/2, "\n");
                    clicPosition = k/2;
                }
            }
            else
            {
                if(k % 2 == 0)
                {
                    LOG(k/2, "\n");
                    clicPosition = k/2;
                }
            }
        }
    }
}
