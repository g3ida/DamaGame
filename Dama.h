#pragma once

#include "GameState.h"
#include "Damier.h"
#include "Player.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Dama : public GameState
{
public:
    Dama();
    virtual void onEnter() override;
    virtual void onClose() override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void draw() const override;
    virtual GameState* handleEvents(InputQueue::Event& e) override;
    virtual GameState* update(unsigned int delay) override;
    virtual ~Dama();
private:
    Damier damier;

    void declareWin(Player* p);

    void play(Player* p);

    float damierX;
    float damierY;
    float damierS;

    enum class State {Turn, Transition, Win};
    State _state = State::Transition;

    Player *_player1 = nullptr, *_player2 = nullptr, *_curentPlayer = nullptr;

    std::vector<std::pair<short int, short int>> possibleMoves;
    std::vector<std::pair<short int, short int>> possibleEats;

    //End Menu stuff.
    int _selectedItem = 0;
    static constexpr int _numItems = 2;

    std::pair<short, short> _lastMove;

    std::array<int, _numItems> _currentSubItem;
    std::array<std::vector<std::string>, _numItems> _items;

    void *_font = GLUT_BITMAP_9_BY_15;
    int _fontWidth = 9;
    int _fontHeight = 15;

    void createEndMenu();
    void drawEndMenu() const;
    GameState* handleEventsEndMenu(InputQueue::Event& e);
};
