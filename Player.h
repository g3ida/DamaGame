#pragma once

#include "Damier.h"
#include <map>

class Player
{
public :
    Player(Damier::Piece color) : m_col (color) {}
    virtual std::pair<short int, short int> makeMove(Damier& dam, std::vector<std::pair<short int, short int>>& moves) = 0;
    inline Damier::Piece getColor() {return m_col;}
    virtual ~Player(){};
protected :
    Damier::Piece m_col = Damier::WHITE;
};

