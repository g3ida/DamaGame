#pragma once

#include "Damier.h"

class Game
{
public :
    void init();
    void update();
    void draw();
    void onKey(unsigned char key, int x, int y);
    void resize(int w, int h);

private :
    Damier damier;
};

