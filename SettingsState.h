#pragma once

#include "GameState.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class SettingsState : public GameState
{
public:
    virtual void onEnter() override;
    virtual void onClose() override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void draw() const override;
    virtual GameState* handleEvents(InputQueue::Event& e) override;
    virtual GameState* update(unsigned int delay) override;
    virtual ~SettingsState();
private:

    void loadSettings();
    void saveSettings();

    int _selectedItem = 0;
    static constexpr int _numItems = 7;

    std::array<int, _numItems> _currentSubItem;
    std::array<std::vector<std::string>, _numItems> _items;

    void *_font = GLUT_BITMAP_9_BY_15;
    int _fontWidth = 9;
    int _fontHeight = 15;
};
