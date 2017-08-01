#include "Dama.h"
#include "Game.h"
#include "logger/log.h"
#include "MenuState.h"
#include "Settings.h"

#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "NotificationSystem.h"

#include <cstdlib>
#include <chrono>

//Handle gcc problem with C++11 threads standard  library on Windows.
#ifdef __MINGW32__
    #include "mingw_threads/mingw.condition_variable.h"
    #include "mingw_threads/mingw.mutex.h"
    #include "mingw_threads/mingw.thread.h"
#else
    #include <thread>
    #include <condition_variable>
    #include <mutex>
#endif // __MINGW32__


#include "Shapes.h"

Player* playerSpawner(Settings::Player p, Damier::Piece col)
{
    switch(p)
    {
    case Settings::Player::Human:
        return new HumanPlayer(col);
        break;
    case Settings::Player::Computer:
        return new ComputerPlayer(col);
        break;
    }
}

Dama::Dama() : damier()
{

}

void
Dama::onEnter()
{
    int w = InputQueue::getInstance().getScreenWidth();
    int h = InputQueue::getInstance().getScreenHeight();

	damierX = w / 2;
	damierY = h / 2;
	damierS = ((w > h)? h : w)*0.75f;

	damier.setSize(Settings::getBoardSize());
	damier.canEatBakward(Settings::canBackwardEat());
	damier.canKingFly(Settings::canKingsFly());
	damier.reset();

	_player1 = playerSpawner(Settings::player1, Damier::WHITE);
	_player2 = playerSpawner(Settings::player2, Damier::BLACK);
	_curentPlayer = _player2;

	createEndMenu();
}

void
Dama::onClose()
{
    damier.clear();
    delete _player1;
    delete _player2;
    _player1 = nullptr;
    _player2 = nullptr;
}

void
Dama::pause()
{

}

void
Dama::resume()
{

}

void
Dama::draw() const
{
    glClearColor(0.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(2);

    damier.draw(damierX, damierY, damierS);

    if(_state == State::Win)
    {
        drawEndMenu();
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

GameState*
Dama::handleEvents(InputQueue::Event& e)
{
    switch(e.type)
    {
    case InputQueue::Event::Type::Reshape:
        {
            int w = InputQueue::getInstance().getScreenWidth();
            int h = InputQueue::getInstance().getScreenHeight();
            damierX = w / 2;
            damierY = h / 2;
            damierS = ((w > h)? h : w)*0.75f;
        }
        break;
    case InputQueue::Event::Type::Keyboard:
        if(e.data.keyboard.key == 27)
            return new MenuState();
        break;
    case InputQueue::Event::Type::Mouse:
        if(e.data.mouse.button == GLUT_LEFT_BUTTON && e.data.mouse.state == GLUT_DOWN)
        {
            int w = damier.getBoardWidth();
            int xtmp = (int)((((e.data.mouse.x - damierX) / damierS) + 0.5f)*w);
            int ytmp = (int)((((e.data.mouse.y - damierY) / damierS) + 0.5f)*w);
            NotificationSystem::Message m;
            m.type = NotificationSystem::Message::Type::ClicTerrain;
            m.data.clicTerrain.boardPos = damier.fromXY(xtmp, ytmp);
            NotificationSystem::getInstance().notifyObservers(m);
        }
        break;
    default:
        break;
    }
    if(_state == State::Win)
    {
        auto tmp =  handleEventsEndMenu(e);
        if (tmp != nullptr)
            return tmp;
    }

    return this;
}

using namespace std::literals::chrono_literals;


GameState*
Dama::update(unsigned int delay)
{  damier.update(delay);
    switch(_state)
    {
    case State::Transition:
        if(!damier.transition())
        {
            if(!possibleEats.empty())
            {
                possibleEats.clear();
                auto v = damier.eatsOf(_lastMove.second);
                if(!v.empty())
                {
                    if(!Settings::mustEatMaxPieces())
                    {
                        for(auto x : v)
                        {
                            possibleEats.push_back(std::make_pair(_lastMove.second, x));
                        }
                    }
                    else
                    {
                        for(auto x : v)
                        {
                            possibleEats.push_back(std::make_pair(_lastMove.second, x));
                        }
                    }
                    _state = State::Turn;
                }
            }
            else
            {
                damier.createKings();
                possibleEats.clear();
                possibleMoves.clear();
                //////////////
                damier.unhighlightAll();
                ////////////////
                _curentPlayer = ((_curentPlayer == _player1)? _player2 : _player1);
                if(Settings::mustEatMaxPieces())
                {
                    possibleEats = damier.getBestPossibleEats(_curentPlayer);
                }
                else
                {
                    possibleEats = damier.getPossibleEats(_curentPlayer);
                }
                _state = State::Turn;
            }
        }
        break;
    case State::Win:
        declareWin(_curentPlayer);
        break;
    case State::Turn:
        play(_curentPlayer);
        break;
    }
    return this;
}

void
Dama::play(Player* p)
{
    //If there are no jumps.
    if(possibleEats.empty())
    {
        //See if there are some available moves.
        if(possibleMoves.empty())
            possibleMoves = damier.getPossibleMoves(p);
        //If there is nothing to do then the player has lost.
        if(possibleMoves.empty())
        {
            _state = State::Win;
            return;
        }
        //Chose one move among the possible ones.
        _lastMove = p->makeMove(damier, possibleMoves);

        //If it is not a thinking state.
        if(_lastMove.first != -1 && _lastMove.second != -1)
        {
            std::this_thread::sleep_for(100ms);
            damier.performMove(_lastMove.first, _lastMove.second);
            _state = State::Transition;
        }
        //If we already chosen a piece to play with.
        else if(_lastMove.first != -1)
        {
            damier.unhighlightAll();
            damier.highlight(_lastMove.first);
            for(auto x : possibleMoves)
                if(x.first == _lastMove.first)
            damier.highlight(x.second);
        }
        //If we haven't selected anything yet.
        else if(_lastMove.first == -1 && _lastMove.second == -1)
        {
            damier.unhighlightAll();
            for(auto x : possibleMoves)
                damier.highlight(x.first);
        }
    }
    else
    {
        std::this_thread::sleep_for(100ms);
        _lastMove = p->makeMove(damier, possibleEats);
        if(_lastMove.first != -1 && _lastMove.second != -1)
        {
            damier.performEat(_lastMove.first, _lastMove.second);
            _state = State::Transition;
        }
        //If we already chosen a piece to play with.
        else if(_lastMove.first != -1)
        {
            damier.unhighlightAll();
            damier.highlight(_lastMove.first);
            for(auto x : possibleEats)
                if(x.first == _lastMove.first)
            damier.highlight(x.second);
        }
        //If we haven't selected anything yet.
        else if(_lastMove.first == -1 && _lastMove.second == -1)
        {
            damier.unhighlightAll();
            for(auto x : possibleEats)
                damier.highlight(x.first);
        }
    }
/*
    for(auto x : possibleEats)
    {
       damier.highlight(x.first);
       //damier.highlight(x.second);
    }

    for(auto x : possibleMoves)
    {
       damier.highlight(x.first);
       //damier.highlight(x.second);
    }*/
}

void Dama::declareWin(Player* p)
{
    NotificationSystem::Message m;
    m.type = NotificationSystem::Message::Type::PlayerWin;
    NotificationSystem::getInstance().notifyObservers(m);
}

void
Dama::createEndMenu()
{
    _items[0].push_back(std::string("Replay"));
    _items[1].push_back(std::string("Back to menu"));
    _currentSubItem[0] = 0;
    _currentSubItem[1] = 0;
}

void
Dama::drawEndMenu() const
{
    glColor4f(0.f, 0.f, 0.f, 0.8f);
    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
    Shapes::drawRectangleFilled(0, 0, InputQueue::getInstance().getScreenWidth(), InputQueue::getInstance().getScreenHeight(), false);

    glColor3f(1.f, 1.f, 1.f);
    std::string s("*** ");
    s += ((_curentPlayer->getColor() == Damier::WHITE)? std::string("Black") : std::string("White"));
    s += std::string(" player wins ! ***");

    glRasterPos2i(damierX - (s.length()/2) * _fontWidth, damierY - damierS /2 - _fontHeight);
    for (auto& c : s)
    {
        glutBitmapCharacter(_font, c);
    }

    int centerX = InputQueue::getInstance().getScreenWidth() * 0.5;
    int centerY = InputQueue::getInstance().getScreenHeight() * 0.5;

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
}

GameState*
Dama::handleEventsEndMenu(InputQueue::Event& e)
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
            switch(_selectedItem)
            {
            case 0:
                return new Dama();
                break;
            case 1:
                return new MenuState();
                break;
            }
            break;
        case 27:
            return new MenuState();
            break;
        }
    }
    return nullptr;
}

Dama::~Dama()
{

}

