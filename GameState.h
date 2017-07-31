#pragma once

#include "InputQueue.h"

class Game;

class GameState
{
public:
    virtual void onEnter() = 0;
    virtual void onClose() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void draw() const = 0;
    virtual GameState* handleEvents(InputQueue::Event& e) = 0;
    virtual GameState* update(unsigned int delay) = 0;
    virtual ~GameState() {}
};
