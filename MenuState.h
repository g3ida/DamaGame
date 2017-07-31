#pragma once

#include "GameState.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <array>

class MenuState : public GameState
{
public:
    MenuState();
    virtual void onEnter() override;
    virtual void onClose() override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void draw() const override;
    virtual GameState* handleEvents(InputQueue::Event& e) override;
    virtual GameState* update(unsigned int delay) override;
    virtual ~MenuState();

private:
    struct Rect{int x,y,w,h;};

    void resetRects();

    int _currentItem = 0;
    static constexpr int _numItems = 5;
    std::array<std::string, _numItems> _menuItems;
    std::array<Rect, _numItems> _itemRects;
    std::array<std::function<GameState*()>, _numItems> _itemCallbacks;
    int _menuItemMaxLength;

    void *_font = GLUT_BITMAP_9_BY_15;
    int _fontWidth = 9;
    int _fontHeight = 15;

};

