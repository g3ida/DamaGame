#include "SettingsState.h"
#include "MenuState.h"
#include "Game.h"
#include "Settings.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void
SettingsState::onEnter()
{

    _items[0].push_back(std::string("Sound volume :  <---------->      "));
    _items[0].push_back(std::string("Sound volume :  <|--------->      "));
    _items[0].push_back(std::string("Sound volume :  <||-------->      "));
    _items[0].push_back(std::string("Sound volume :  <|||------->      "));
    _items[0].push_back(std::string("Sound volume :  <||||------>      "));
    _items[0].push_back(std::string("Sound volume :  <|||||----->      "));
    _items[0].push_back(std::string("Sound volume :  <||||||---->      "));
    _items[0].push_back(std::string("Sound volume :  <|||||||--->      "));
    _items[0].push_back(std::string("Sound volume :  <||||||||-->      "));
    _items[0].push_back(std::string("Sound volume :  <|||||||||->      "));
    _items[0].push_back(std::string("Sound volume :  <||||||||||>      "));

    _items[1].push_back(std::string("Game rules   : <International>    "));
    _items[1].push_back(std::string("Game rules   : <   English   >    "));
    _items[1].push_back(std::string("Game rules   : <   Canadian  >    "));
    _items[1].push_back(std::string("Game rules   : <   Custom    >    "));

    _items[2].push_back(std::string("      > Flying King    : <   No  >"));
    _items[2].push_back(std::string("      > Flying King    : <  Yes  >"));

    _items[3].push_back(std::string("      > Backward eat   : <   No  >"));
    _items[3].push_back(std::string("      > Backward eat   : <  Yes  >"));

    _items[4].push_back(std::string("      > Eat max pieces : <   No  >"));
    _items[4].push_back(std::string("      > Eat max pieces : <  Yes  >"));

    _items[5].push_back(std::string("      > Board size     : <  8x8  >"));
    _items[5].push_back(std::string("      > Board size     : < 10x10 >"));
    _items[5].push_back(std::string("      > Board size     : < 12x12 >"));

    _items[6].push_back(std::string("< Discard changes >"));
    _items[6].push_back(std::string("<  Reset default  >"));
    _items[6].push_back(std::string("<   Save changes  >"));

    _currentSubItem[0] = 5;
    _currentSubItem[1] = 0;
    _currentSubItem[2] = 1;
    _currentSubItem[3] = 1;
    _currentSubItem[4] = 1;
    _currentSubItem[5] = 1;
    _currentSubItem[6] = 0;

    loadSettings();

}

void
SettingsState::loadSettings()
{
    //Sound Volume.
    _currentSubItem[0] = static_cast<int>(Settings::getSoundVolume() * _items[1].size());

    if(_currentSubItem[0] < 0) _currentSubItem[1] = 0;
    if(_currentSubItem[0] >= _items[0].size()) _currentSubItem[0] = _items[0].size()-1;
    switch(Settings::getRule())
    {
    case Settings::Rule::International:
        _currentSubItem[1] = 0;
        _currentSubItem[2] = 1;
        _currentSubItem[3] = 1;
        _currentSubItem[4] = 1;
        _currentSubItem[5] = 1;
        break;
    case Settings::Rule::English:
        _currentSubItem[1] = 1;
        _currentSubItem[2] = 1;
        _currentSubItem[3] = 0;
        _currentSubItem[4] = 0;
        _currentSubItem[5] = 0;
        break;
    case Settings::Rule::Canadian:
        _currentSubItem[1] = 2;
        _currentSubItem[2] = 1;
        _currentSubItem[3] = 1;
        _currentSubItem[4] = 1;
        _currentSubItem[5] = 2;
        break;
    case Settings::Rule::Custom:
        _currentSubItem[1] = 3;
        _currentSubItem[2] = Settings::canKingsFly();
        _currentSubItem[3] = Settings::canBackwardEat();
        _currentSubItem[4] = Settings::mustEatMaxPieces();
        _currentSubItem[5] = ((Settings::getBoardSize() == 8)? 0 : (Settings::getBoardSize() == 10)? 1 : 2);;
        break;
    }
}

void
SettingsState::saveSettings()
{
    Settings::setSoundVolume((float)_currentSubItem[0] /(float) _items[0].size());
    switch(_currentSubItem[1])
    {
    case 0:
        Settings::setRule(Settings::Rule::International);
        break;
    case 1:
        Settings::setRule(Settings::Rule::English);
        break;
    case 2:
        Settings::setRule(Settings::Rule::Canadian);
        break;
    case 3:
        Settings::setRule(Settings::Rule::Custom);
        Settings::setFlyingKings(_currentSubItem[2]);
        Settings::setBackwardEat(_currentSubItem[3]);
        Settings::setEatMaxPieces(_currentSubItem[4]);
        Settings::setBoardSize(((_currentSubItem[5] == 0)? 8 : ((_currentSubItem[5] == 1)? 10 : 12)));
        break;
    }
}

void
SettingsState::onClose()
{

}
void
SettingsState::pause()
{

}

void
SettingsState::resume()
{

}

void
SettingsState::draw() const
{
    glClearColor(0.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    int centerX = InputQueue::getInstance().getScreenWidth() * 0.5;
    int centerY = InputQueue::getInstance().getScreenHeight()* 0.5;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.f, 1.f, 1.f);
    std::string s("Settings");
    glRasterPos2i(centerX-s.length()*9*0.5, centerY*0.2);
    for (auto& c : s)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18  , c);
    }

    for(int i=0; i<_numItems; ++i)
    {
        glColor3f(1.f, 1.f, 1.f);
        if(_selectedItem == i) glColor3f(1.f, 1.f, 0.2f);
        glRasterPos2i(centerX-_items[i][_currentSubItem[i]].length()/2*_fontWidth, centerY - _fontHeight*(-2*i+_numItems));
        for (auto& c : _items[i][_currentSubItem[i]])
        {
            glutBitmapCharacter(_font, c);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

GameState*
SettingsState::handleEvents(InputQueue::Event& e)
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
                if(_currentSubItem[_selectedItem] ==  _items[_selectedItem].size())
                    _currentSubItem[_selectedItem] = 0;
                break;
            }
        break;
    case InputQueue::Event::Type::Keyboard:
        switch(e.data.keyboard.key)
        {
        case 13:
            if(_selectedItem == 6)
            {
                switch(_currentSubItem[6])
                {
                case 0:
                    return new MenuState();
                    break;
                case 1:
                    Settings::resetDefaults();
                    loadSettings();
                    break;
                case 2:
                    saveSettings();
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

    if(e.type == InputQueue::Event::Type::KeyboardSpecial &&
       (e.data.keyboardSpecial.key == GLUT_KEY_LEFT || e.data.keyboardSpecial.key == GLUT_KEY_RIGHT))
    {
        switch(_selectedItem)
        {
        case 1:
            switch(_currentSubItem[_selectedItem])
            {
            case 0:
                _currentSubItem[2] = 1;
                _currentSubItem[3] = 1;
                _currentSubItem[4] = 1;
                _currentSubItem[5] = 1;
                break;
            case 1:
                _currentSubItem[2] = 1;
                _currentSubItem[3] = 0;
                _currentSubItem[4] = 0;
                _currentSubItem[5] = 0;
                break;
            case 2:
                _currentSubItem[2] = 1;
                _currentSubItem[3] = 1;
                _currentSubItem[4] = 1;
                _currentSubItem[5] = 2;
                break;
            case 3:
                break;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            _currentSubItem[1] = 3;
            break;
        }
    }


    return this;
}

GameState*
SettingsState::update(unsigned int delay)
{
    return this;
}

SettingsState::~SettingsState()
{

}
