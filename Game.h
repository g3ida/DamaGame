#pragma once

#include "Damier.h"
#include <string>

class Game
{
public :
    void init(const std::string& windowTitle);
    void quit();

    void update();
    void draw();
    void onKey(unsigned char key, int x, int y);
    void onMouse(int button, int state, int x, int y);
    void resize(int w, int h);
    //Need to add save and load functions.

    //Singleton design pattern.
    static Game& getInstance();

    //Returns the game window.
    int getWindow();

private :
    //Disable instantiation.
    Game();
    Damier damier;

    //The glut widow handle of the game instance.
    int gameWindow = 0;

    //For the board settings
    float damierX;
    float damierY;
    float damierS;

    //Used to map mouse events.
    float screenWidth;
    float screenHeight;

};

