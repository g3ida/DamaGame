#include "PlayState.h"
#include "Game.h"
#include "logger/log.h"
#include "MenuState.h"
#include "Settings.h"
#include "Dama.h"

void
PlayState::onEnter()
{
    _items[0].push_back(std::string("Player 1   : <   Human  >"));
    _items[0].push_back(std::string("Player 1   : < Computer >"));
    //_items[0].push_back(std::string("Player 1   : <  Network >"));

    _items[1].push_back(std::string("Player 2   : <   Human  >"));
    _items[1].push_back(std::string("Player 2   : < Computer >"));
    //_items[0].push_back(std::string("Player 2   : <  Network >"));

    _items[2].push_back(std::string("< Start game >"));
    _items[2].push_back(std::string("< Back to menu >"));

    _currentSubItem[0] = ((Settings::player1 == Settings::Player::Human)? 0 : 1);
    _currentSubItem[1] = ((Settings::player2 == Settings::Player::Human)? 0 : 1);
    _currentSubItem[2] = 0;

}

void
PlayState::onClose()
{

}

void
PlayState::pause()
{

}

void
PlayState::resume()
{

}

void
PlayState::draw() const
{
    glClearColor(0.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    int centerX = InputQueue::getInstance().getScreenWidth() * 0.5;
    int centerY = InputQueue::getInstance().getScreenHeight() * 0.5;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.f, 1.f, 1.f);
    std::string s("New game");
    glRasterPos2i(centerX-s.length()*9*0.5, centerY*0.2);
    for (auto& c : s)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18  , c);
    }

    for(int i=0; i<_numItems; ++i)
    {
        glColor3f(1.f, 1.f, 1.f);
        if(_selectedItem == i) glColor3f(1.f, 1.f, 0.2f);
        glRasterPos2i(centerX-_items[i][_currentSubItem[i]].length()/2*_fontWidth,centerY - _fontHeight*(-2*i+1));
        for (auto& c : _items[i][_currentSubItem[i]])
        {
            glutBitmapCharacter(_font, c);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

GameState*
PlayState::handleEvents(InputQueue::Event& e)
{
    switch(e.type)
    {
    case InputQueue::Event::Type::KeyboardSpecial:
            switch(e.data.keyboardSpecial.key)
            {
            case GLUT_KEY_UP:
                _selectedItem--; if(_selectedItem < 0) _selectedItem += _numItems;
                break;
            case GLUT_KEY_DOWN:
                _selectedItem++; _selectedItem %= _numItems;
                break;
            case GLUT_KEY_LEFT:
                _currentSubItem[_selectedItem]--;
                if(_currentSubItem[_selectedItem] < 0)
                    _currentSubItem[_selectedItem] += _items[_selectedItem].size();
                break;
            case GLUT_KEY_RIGHT:
                _currentSubItem[_selectedItem]++;
                if(_currentSubItem[_selectedItem] ==  (int)_items[_selectedItem].size())
                    _currentSubItem[_selectedItem] = 0;
                break;
            }
        break;
    case InputQueue::Event::Type::Keyboard:
        switch(e.data.keyboard.key)
        {
        case 13:
            if(_selectedItem == 2)
            {
                switch(_currentSubItem[2])
                {
                case 0:
                    Settings::player1 = ((_currentSubItem[0] == 0)? Settings::Player::Human : Settings::Player::Computer);
                    Settings::player2 = ((_currentSubItem[1] == 0)? Settings::Player::Human : Settings::Player::Computer);
                    return new Dama();
                    break;
                case 1:
                    return new MenuState();
                    break;
                }
            }
            break;
        case 27:
            return new MenuState();
            break;
        }
    }
    return this;
}

GameState*
PlayState::update(unsigned int delay)
{
    return this;
}

PlayState::~PlayState()
{

}
