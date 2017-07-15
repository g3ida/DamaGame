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
    void draw(float y, float x, float size);
    bool isEmpty(short x);
    bool isWhite(short x);
    std::vector<short>&& whiteNormalMouvement(short x);
    std::vector<short>&& blackNormalMouvement(short x);
    std::vector<short>&& kingMouvement(short x);

    std::vector<short>&& whiteNormalEat(short x);
    std::vector<short>&& blackNormalEat(short x);
    std::vector<short>&& whiteKingEat(short x);
    std::vector<short>&& blackKingEat (short x);



private :
    static const int SIZE = 50;
    Piece tab[SIZE];
    short eatBlackDownRight (short x);
    short eatBlackDownLeft (short x);
    short eatWhiteDownRight (short x);
    short eatWhiteDownLeft (short x);
    short eatWhiteUpRight (short x);
    short eatWhiteUpLeft (short x);
    short eatBlackUpRight (short x);
    short eatBlackUpLeft (short x);
};
