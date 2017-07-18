#pragma once

#include <vector>
#include <map>
#include "Log.h"

class Player;

class Damier
{
public :
    enum Piece{EMPTY = 0x00, WHITE = 0x01 , BLACK = 0x04 , WHITE_KING = 0x03, BLACK_KING = 0x0C};
    Damier();
    void reset();
    void clear();
    void set(Piece p, int i);
    Piece at(int i); //Retourne le type de la piece
    void draw(float y, float x, float size);
    bool isEmpty(short x);
    bool isWhite(short x);

    void performMove(short i, short j);
    void performEat(short i, short j);

    std::vector<short> movesOf(short x);
    std::vector<short> eatsOf(short x);

    std::vector<std::pair<short int, short int>> getPossibleMoves(Player *p);
    std::vector<std::pair<short int, short int>> getPossibleEats(Player *p);


private :
    std::vector<short> whiteManMove(short x);
    std::vector<short> blackManMove(short x);
    std::vector<short> kingMove(short x);

    std::vector<short> whiteManEat(short x);
    std::vector<short> blackManEat(short x);
    std::vector<short> whiteKingEat(short x);
    std::vector<short> blackKingEat(short x);

    short eatBlackDownRight(short x);
    short eatBlackDownLeft(short x);
    short eatWhiteDownRight(short x);
    short eatWhiteDownLeft(short x);
    short eatWhiteUpRight(short x);
    short eatWhiteUpLeft(short x);
    short eatBlackUpRight(short x);
    short eatBlackUpLeft(short x);

    static const int SIZE = 50;
    Piece tab[SIZE];
};
