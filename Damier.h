#pragma once

#include <vector>
#include <map>
#include <array>
#include "logger/Log.h"

class Player;

class Damier
{
public :
    enum Piece{EMPTY = 0x00, WHITE = 0x01 , BLACK = 0x04 , WHITE_KING = 0x03, BLACK_KING = 0x0C};

    Damier();

    void reset();
    void clear();

    //updating pieces position to perform animation.
    void update(int dt);
    bool transition();
    std::pair<float, float> getTransitionActualPos();

    void set(Piece p, int i);
    Piece at(int i) const; //Retourne le type de la piece

    bool isEmpty(short x) const;
    bool isWhite(short x) const;

    void setSize(int sz);
    int getSize() const;

    void draw(float y, float x, float size) const;

    void performMove(short i, short j);
    //Returns the position of the eat. Can be quite handy.
    short performEat(short i, short j);

    std::vector<short> movesOf(short x) const;
    std::vector<short> eatsOf(short x);

    void createKings();

    std::vector<std::pair<short int, short int>> getPossibleMoves(Player *p) const;
    std::vector<std::pair<short int, short int>> getPossibleEats(Player *p);
    std::vector<std::pair<short int, short int>> getBestPossibleEats(Player *p);
    std::pair<short int, short int> bestEatOf(short i);
    int maxConsecutiveEats(short i);

    //Some conversion functions useful for drawing and other things.
    std::pair<short, short> toXY(short x) const;
    short fromXY(short x, short y) const;

    short decrementRight(short x) const;
    short decrementLeft(short x) const;
    short incrementLeft(short x) const;
    short incrementRight(short x) const;

    //float getBoardFromPosition(float x, float y);
    int getBoardWidth() const;
    void canEatBakward(bool b);
    void canKingFly(bool b);

    void highlight(short x);
    void unhighlightAll();


private :
    std::vector<short> whiteManMove(short x) const;
    std::vector<short> blackManMove(short x) const;
    std::vector<short> kingMove(short x) const;

    std::vector<short> whiteManEat(short x) const;
    std::vector<short> blackManEat(short x) const;
    std::vector<short> whiteKingEat(short x);
    std::vector<short> blackKingEat(short x);

    short eatBlackDownRight(short x) const;
    short eatBlackDownLeft(short x) const;
    short eatWhiteDownRight(short x) const;
    short eatWhiteDownLeft(short x) const;
    short eatWhiteUpRight(short x) const;
    short eatWhiteUpLeft(short x) const;
    short eatBlackUpRight(short x) const;
    short eatBlackUpLeft(short x) const;

    static constexpr int MAX_SIZE = 72;

    struct BoardInfo
    {
        int width;
        int boardSize;
        int numPieces;
    };

    std::array<BoardInfo, 3> _boardInfo;
    int _board = 1;

    bool _eatBackward = true;
    bool _flyingKing = true;

    //For performing animation.
    bool _isTransition = false;
    float _transitionX, _transitionY;
    int _trSrcX, _trSrcY, _trDestX, _trDestY;
    Piece _typeTr;
    bool _isEat = false;
    short _eatPos;

    std::vector<int> _highlighted;

    Piece tab[MAX_SIZE];
};

