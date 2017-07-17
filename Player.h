#pragma once

#include "Damier.h"
#include <map>

class Player
{
public :
    Player(Damier::Piece color) : m_col (color) {}
    std::pair<short int, short int> makeMove(Damier& dam, std::vector<std::pair<short int, short int>>& moves);
    inline Damier::Piece getColor() {return m_col;}
private :
    bool m_isWhite = true;
    Damier::Piece m_col = Damier::WHITE;
};
