#pragma once

#include <vector>

class Damier
{
public :
    enum Piece{EMPTY, WHITE, BLACK, WHITE_KING, BLACK_KING};
    Damier();
    void reset();
    void clear();
    void set(Piece p, int i);
    Piece at(int i); //Retourne le type de la piece
    void draw(float y, float x);

    std::vector<short> whiteNormalMouvement(short x);
    std::vector<short> blackNormalMouvement(short x);
    std::vector<short> whiteKingMouvement(short x);
    std::vector<short> blackKingMouvement(short x);



private :
    static const int SIZE = 50;
    Piece tab[SIZE];
};
