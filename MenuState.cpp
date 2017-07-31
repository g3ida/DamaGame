#include "MenuState.h"
#include "logger/Log.h"
#include "Game.h"
#include "PlayState.h"
#include "SettingsState.h"
#include "AchievmentsState.h"
#include "CreditsState.h"
#include "Shapes.h"
#include <string>
#include <algorithm>

void
MenuState::resetRects()
{
    int w = _menuItemMaxLength * _fontWidth * 2;
    int h = _fontHeight * 2;
    int x = InputQueue::getInstance().getScreenWidth() * 0.5;

    int centerY = InputQueue::getInstance().getScreenHeight() * 0.5;
    for(int i=0; i < _numItems; ++i)
    {
        int y = centerY - ((_numItems-1) * 0.5 - i) * _fontHeight * 4;
        _itemRects[i].x = x;
        _itemRects[i].y = y;
        _itemRects[i].w = w;
        _itemRects[i].h = h;
    }
}

MenuState::MenuState() : _menuItems{std::string("Play"), std::string("Achievements"),std::string("Settings"),
                        std::string("Credits"), std::string("Quit")},
                        _itemCallbacks{[](){return new PlayState();}, [](){return new AchievmentsState();},
                        [](){return new SettingsState();}, [](){return new CreditsState();}, [](){return nullptr;}}
{
    _menuItemMaxLength = std::max_element(_menuItems.begin(), _menuItems.end(), [](auto a, auto b){return a.length() < b.length();})->length();
}

void
MenuState::onEnter()
{
    resetRects();
}

void
MenuState::onClose()
{

}

void
MenuState::pause()
{

}

void
MenuState::resume()
{

}

void
MenuState::draw() const
{
    glClearColor(0.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.f, 1.f, 1.f);
    std::string s("Jeu de Dames");
    int centerX = InputQueue::getInstance().getScreenWidth() / 2;
    int centerY = InputQueue::getInstance().getScreenHeight() / 2;
    glRasterPos2i(centerX-s.length()*9*0.5, centerY*0.2);
    for (auto& c : s)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18  , c);
    }

    //Draw squares.
    for(int i=0; i< _numItems; ++i)
    {
        glColor3f(0.f, 0.2656f, 0.2656f);
        if(i == _currentItem)
        {
            glColor3f(0.f, 1.f, 0.2656f);
        }
        Shapes::drawRectangleFilled(_itemRects[i].x, _itemRects[i].y, _itemRects[i].w, _itemRects[i].h);
    }

    //Draw menu entries.
    glColor3f(1.f, 1.f, 1.f);
    for(int i=0; i < _numItems; ++i)
    {
        glRasterPos2i(_itemRects[i].x - _menuItems[i].size() * 0.5 * _fontWidth, _itemRects[i].y + _fontHeight * 0.33);
        for (auto& c : _menuItems[i])
        {
            glutBitmapCharacter(_font, c);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

GameState*
MenuState::handleEvents(InputQueue::Event& e)
{
    switch(e.type)
    {
    case InputQueue::Event::Type::KeyboardSpecial:
        if(e.data.keyboardSpecial.key ==  GLUT_KEY_UP)
        {
            _currentItem--;
            if(_currentItem < 0) _currentItem += _numItems;
        }
        else if(e.data.keyboardSpecial.key == GLUT_KEY_DOWN)
        {
            _currentItem++;
            _currentItem %= _numItems;
        }
        break;
    case InputQueue::Event::Type::Keyboard:
        if(e.data.keyboard.key == 13)
        {
            return _itemCallbacks[_currentItem]();
        } else if(e.data.keyboard.key == 27)
        {
            return nullptr;
        }
        break;
    case InputQueue::Event::Type::Reshape:
        resetRects();
        break;
    case InputQueue::Event::Type::Mouse:
        if(e.data.mouse.button == GLUT_LEFT_BUTTON && e.data.mouse.state == GLUT_DOWN)
        {
            std::pair<int, int> mouse = InputQueue::getInstance().getMouseCoords();
            if(mouse.first > _itemRects[_currentItem].x - _itemRects[_currentItem].w * 0.5 &&
                mouse.first < _itemRects[_currentItem].x + _itemRects[_currentItem].w * 0.5 &&
                mouse.second > _itemRects[_currentItem].y - _itemRects[_currentItem].h * 0.5&&
                mouse.second < _itemRects[_currentItem].y + _itemRects[_currentItem].h * 0.5)
            {
                return _itemCallbacks[_currentItem]();
            }
        }
        break;

    }

    return this;
}

GameState*
MenuState::update(unsigned int delay)
{
    std::pair<int, int> mouse = InputQueue::getInstance().getMouseCoords();
    for(int i=0; i<_numItems; ++i)
    {
        if(mouse.first > _itemRects[i].x - _itemRects[i].w * 0.5 &&
            mouse.first < _itemRects[i].x + _itemRects[i].w * 0.5 &&
            mouse.second > _itemRects[i].y - _itemRects[i].h * 0.5&&
            mouse.second < _itemRects[i].y + _itemRects[i].h * 0.5)
        {
            _currentItem = i;
            break;
        }
    }
    return this;
}


MenuState::~MenuState()
{

}
