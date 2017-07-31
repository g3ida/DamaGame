#pragma once

#include "GameState.h"
#include <string>

class CreditsState : public GameState
{
public:
    virtual void onEnter() override;
    virtual void onClose() override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void draw() const override;
    virtual GameState* handleEvents(InputQueue::Event& e) override;
    virtual GameState* update(unsigned int delay) override;
    virtual ~CreditsState();
private:
    std::string _creditsString;
};

