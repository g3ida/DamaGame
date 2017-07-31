#pragma once

#include "GameState.h"

#include <memory>
#include <vector>

#include <ctime>


class Game
{
public:
    //Function object for the thread call.
    void operator()();
    void draw();
    void quit();

    static Game& getInstance();

    void changeState(GameState* state);
    void pushState(GameState* state);
    void popState();
    bool isStateStackEmpty();
private:
    Game();
    std::vector<GameState*> _stateStack;
    std::recursive_mutex _stack_mtx;

    int _screenW = 640, _screenH = 480;

    std::clock_t _begin;
    std::clock_t _end;

};
