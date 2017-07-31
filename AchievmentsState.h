#pragma once

#include "GameState.h"

class AchievmentsState : public GameState
{
public:
    virtual void onEnter() override;
    virtual void onClose() override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void draw() const override;
    virtual GameState* handleEvents(InputQueue::Event& e) override;
    virtual GameState* update(unsigned int delay) override;
    virtual ~AchievmentsState();
private:
};


