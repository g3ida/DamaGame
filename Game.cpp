#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

#include "Game.h"
#include "Log.h"

#include "Shapes.h"
#include "Utils.h"

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
    mySleep(100);
    glutPostRedisplay();

    switch(currentState)
    {
    case TURN_1:
        play(player1);
        break;
    case TURN_2:
        play(player2);
        break;
    case VICTORY_1:
        LOG("player 1 won\n");
        break;
    case VICTORY_2:
        LOG("player 2 won\n");
        break;
    case DRAW:
        LOG("it's a draw");
        break;
    }
}

void
Game::play(Player* p)
{
    if(turnFirstPass)
    {
        possiblePlays.clear();
        possiblePlays = damier.getPossibleEats(p);
        turnFirstPass = false;
    }
    //If there are no jumps.
    if(possiblePlays.empty())
    {
        //See if there are some available moves.
        possiblePlays = damier.getPossibleMoves(p);
        //If there is nothing to do then the player has lost.
        if(possiblePlays.empty())
        {
            currentState = ((currentState == TURN_1) ? VICTORY_2 : VICTORY_1);
            return;
        }
        //Chose one move among the possible ones.
        auto m = p->makeMove(damier, possiblePlays);

        if(damier.at(m.first) == Damier::BLACK_KING || damier.at(m.first) == Damier::WHITE_KING)
        {
            LOG(m.first, " king Move ", m.second);
        }

        //If it is not a thinking state.
        if(m.first != -1)
        {
            mySleep(200);
            currentState = ((currentState == TURN_1) ? TURN_2 : TURN_1);
            turnFirstPass = true;
            damier.performMove(m.first, m.second);
        }
    }
    else
    {
        mySleep(200);
        auto m = p->makeMove(damier, possiblePlays);

        if(damier.at(m.first) == Damier::BLACK_KING || damier.at(m.first) == Damier::WHITE_KING)
        {
            LOG(m.first, " king Eat ", m.second);
        }
        damier.performEat(m.first, m.second);
        currentState = ((currentState == TURN_1) ? TURN_2 : TURN_1);
        turnFirstPass = true;
    }
    damier.createKings();
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
