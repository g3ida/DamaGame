#include "CreditsState.h"
#include "Game.h"
#include "MenuState.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void
CreditsState::onEnter()
{
    _creditsString = std::string("Game created by Mohamed Alaa Eddine Gaida");
}

void
CreditsState::onClose()
{

}

void
CreditsState::pause()
{

}

void
CreditsState::resume()
{

}

void
CreditsState::draw() const
{
    glClearColor(0.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    std::string s("Credits");
    int centerX = InputQueue::getInstance().getScreenWidth() / 2;
    int centerY = InputQueue::getInstance().getScreenHeight() / 2;
    glRasterPos2i(centerX-s.length()*9*0.5, centerY*0.2);
    for (auto& c : s)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18  , c);
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

GameState*
CreditsState::handleEvents(InputQueue::Event& e)
{
    switch(e.type)
    {
    case InputQueue::Event::Type::Keyboard:
        if(e.data.keyboard.key == 27)
            return new MenuState();
        break;
    }

    return this;
}

GameState*
CreditsState::update(unsigned int delay)
{
    return this;
}

CreditsState::~CreditsState()
{

}
