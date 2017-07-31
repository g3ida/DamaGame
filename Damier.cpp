#include "Damier.h"
#include <GL/glut.h>
#include "Shapes.h"
#include "logger/Log.h"
#include "Player.h"
#include <functional>

#include <algorithm>

Damier::Damier()
{
    _boardInfo[0].width = 10;
    _boardInfo[0].boardSize = 50;
    _boardInfo[0].numPieces = 20;

    _boardInfo[1].width = 8;
    _boardInfo[1].boardSize = 32;
    _boardInfo[1].numPieces = 12;

    _boardInfo[2].width = 12;
    _boardInfo[2].boardSize = 72;
    _boardInfo[2].numPieces = 30;

    reset();
}

void
Damier::clear()
{
    for(int i=0; i< MAX_SIZE; i++)
        tab[i] = EMPTY;
}

void
Damier::reset()
{
    clear();
    for(int i=0; i<_boardInfo[_board].numPieces; i++)
    {
        tab[i] = BLACK;
        tab[_boardInfo[_board].boardSize-i-1] = WHITE;
    }
}

void
Damier::set(Piece p, int i)
{
    if(i < 0 || i > _boardInfo[_board].boardSize)
        return;

    tab[i] = p;

}

Damier::Piece
Damier::at(int i) const
{
    if(i < 0 || i >= _boardInfo[_board].boardSize)
        return EMPTY;

    return tab[i];
}

bool Damier::isEmpty(short x) const
{
    return (at(x) == EMPTY);
}

bool Damier::isWhite(short x) const
{
    return (at(x) == WHITE || at(x) == WHITE_KING);

}

void Damier::setSize(int sz)
{
    if(sz == 8) _board = 1;
    else if(sz == 10) _board = 0;
    else if(sz == 12) _board = 2;
}

int Damier::getSize() const
{
    return _boardInfo[_board].width;
}

short Damier::decrementRight(short x) const
{
    auto y = toXY(x);
    return fromXY(y.first+1, y.second-1);
}

short Damier::decrementLeft(short x) const
{
    auto y = toXY(x);
    return fromXY(y.first-1, y.second-1);
}
short Damier::incrementLeft(short x) const
{
    auto y = toXY(x);
    return fromXY(y.first-1, y.second+1);
}
short Damier::incrementRight(short x) const
{
    auto y = toXY(x);
    return fromXY(y.first+1, y.second+1);
}
std::vector<short>
Damier::whiteManMove(short x) const
{
    std::vector<short> v;
    short a=decrementLeft(x);
    short b=decrementRight(x);
    if( (a !=(-1)) && tab[a] == EMPTY)
    {
        v.push_back(a);
    }
    if( (b!=(-1)) && tab[b] == EMPTY )
    {
        v.push_back(b);
    }
    return v;
}
std::vector<short>
Damier::blackManMove(short x) const
{
    std::vector<short> v;
    short a=incrementLeft(x);
    short b=incrementRight(x);
    if( (a !=(-1)) && tab[a] == EMPTY )
        v.push_back(a);
    if( (b!=(-1)) && tab[b] == EMPTY )
        v.push_back(b);
    return v;
}
std::vector<short>
Damier::kingMove(short x) const
{
    std::vector<short> v;

    if(!_flyingKing)
    {
        auto v1 = blackManMove(x);
        auto v2 = whiteManMove(x);

         v.insert( v.end(), v1.begin(), v1.end());
         v.insert( v.end(), v2.begin(), v2.end());
         return v;
    }

    short t[]={incrementLeft(x), incrementRight(x), decrementLeft(x), decrementRight(x)};
    for (auto e : t)
    {
        while(e != (-1) && (isEmpty(e)))
        {
            v.push_back(e);
            e = incrementLeft(e);
        }
    }
    return v;
}

short Damier::eatBlackDownLeft(short x) const
{
    short a=decrementLeft(x);
    if(a != (-1))
    {
        short b=decrementLeft(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((!(this->isWhite(a))) && this->isEmpty(b))
                return(b);
        }
    }
    return -1;
}
short Damier::eatBlackDownRight(short x) const
{
    short a=decrementRight(x);
    if(a != (-1))
    {
        short b= decrementRight(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((!(this->isWhite(a))) && this->isEmpty(b))
                return(b);
        }
    }

    return -1;
}
short Damier::eatWhiteDownRight(short x) const
{
    short a=decrementRight(x);
    if(a != (-1))
    {
        short b= decrementRight(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((this->isWhite(a)) && this->isEmpty(b))
                return(b);
        }
    }
    return -1;
}
short Damier::eatWhiteDownLeft(short x) const
{
    short a=decrementLeft(x);
    if(a != (-1))
    {
        short b= decrementLeft(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((this->isWhite(a)) && this->isEmpty(b))
                return(b);
        }
    }
    return -1;
}
short Damier::eatWhiteUpLeft(short x) const
{
    short a=incrementLeft(x);
    if(a != (-1))
    {
        short b= incrementLeft(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((this->isWhite(a)) && this->isEmpty(b))
                return(b);
        }
    }
    return -1;
}
short Damier::eatWhiteUpRight(short x) const
{
    short a=incrementRight(x);
    if(a != (-1))
    {
        short b= incrementRight(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((this->isWhite(a)) && this->isEmpty(b))
                return(b);
        }
    }
    return -1;
}
short Damier::eatBlackUpLeft(short x) const
{
    short a=incrementLeft(x);
    if(a != (-1))
    {
        short b= incrementLeft(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((!(this->isWhite(a))) && this->isEmpty(b))
                return(b);
        }
    }
    return -1;
}
short Damier::eatBlackUpRight(short x) const
{
    short a=incrementRight(x);
    if(a != (-1))
    {
        short b= incrementRight(a);
        if ((!(this->isEmpty(a))) && b!=(-1))
        {
            if((!(this->isWhite(a))) && this->isEmpty(b))
                return(b);
        }
    }
    return -1;
}

std::vector<short>
Damier::whiteManEat(short x) const
{
    std::vector<short> v;

    short a = -1, b = -1, c = -1, d = -1;

    if(_eatBackward)
    {
        c=this->eatBlackUpRight(x);
        d=this->eatBlackUpLeft(x);
    }
    a=this->eatBlackDownRight(x);
    b=this->eatBlackDownLeft(x);

    if(a != -1)
        v.push_back(a);
    if(b != -1)
        v.push_back(b);
    if(c != -1)
        v.push_back(c);
    if(d != -1)
        v.push_back(d);

    return v;
}
std::vector<short> Damier::blackManEat(short x) const
{
    std::vector<short> v;

    short a = -1, b = -1, c = -1, d = -1;
    if(_eatBackward)
    {
        c=this->eatWhiteDownRight(x);
        d=this->eatWhiteDownLeft(x);
    }
    a=this->eatWhiteUpRight(x);
    b=this->eatWhiteUpLeft(x);

    if(a != -1)
        v.push_back(a);
    if(b != -1)
        v.push_back(b);
    if(c != -1)
        v.push_back(c);
    if(d != -1)
        v.push_back(d);
    return v;
}


std::vector<short>
Damier::whiteKingEat(short x)
{
    std::vector<short> v;

    if(!_flyingKing)
    {
        auto tmp = _eatBackward;
        _eatBackward = true;
        v = whiteManEat(x);
        _eatBackward = tmp;
        return v;
    }

    short a=incrementLeft(x);
    short b=incrementRight(x);
    short c=decrementLeft(x);
    short d=decrementRight(x);
    short a1=x,b1=x,c1=x,d1=x;
    while(a!=(-1) && this->isEmpty(a))
    {
        a1=a;
        a=incrementLeft(a); // at the end, a will take the first non empty place or -1 and a1 take the place before
    }

    if(a!=(-1))
    {
        short e=this->eatBlackUpLeft(a1);
        if(e != -1)
        {
            v.push_back(e);
            e=incrementLeft(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=incrementLeft(e);
            }
        }
    }

    while(b!=(-1) && this->isEmpty(b))
    {
        b1=b;
        b=incrementRight(b);
    }
    if(b!=(-1))
    {
        short e=this->eatBlackUpRight(b1);
        if(e != -1)
        {
            v.push_back(e);
            e=incrementRight(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=incrementRight(e);
            }
        }
    }

    while(c!=(-1) && this->isEmpty(c))
    {
        c1=c;
        c=decrementLeft(c);
    }
    if(c!=(-1))
    {
        short e=this->eatBlackDownLeft(c1);
        if(e != -1)
        {
            v.push_back(e);
            e=decrementLeft(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=decrementLeft(e);
            }
        }
    }

    while(d!=(-1) && this->isEmpty(d))
    {
        d1=d;
        d=decrementRight(d);
    }
    if(d!=(-1))
    {
        short e=this->eatBlackDownRight(d1);
        if(e != -1)
        {
            v.push_back(e);
            e=decrementRight(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=decrementRight(e);
            }
        }
    }
    return v;
}

std::vector<short>
Damier::blackKingEat(short x)
{
    std::vector<short> v;

    if(!_flyingKing)
    {
        auto tmp = _eatBackward;
        _eatBackward = true;
        v = blackManEat(x);
        _eatBackward = tmp;
        return v;
    }

    short a=incrementLeft(x);
    short b=incrementRight(x);
    short c=decrementLeft(x);
    short d=decrementRight(x);
    short a1=x,b1=x,c1=x,d1=x;
    while(a!=(-1) && this->isEmpty(a))
    {
        a1=a;
        a=incrementLeft(a); // at the end, a will take the first non empty place or -1 and a1 take the place before
    }

    if(a!=(-1))
    {
        short e=this->eatWhiteUpLeft(a1);
        if(e != -1)
        {
            v.push_back(e);
            e=incrementLeft(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=incrementLeft(e);
            }
        }
    }
    while(b!=(-1) && this->isEmpty(b))
    {
        b1=b;
        b=incrementRight(b);
    }
    if(b!=(-1))
    {
        short e=this->eatWhiteUpRight(b1);
        if(e != -1)
        {
            v.push_back(e);
            e=incrementRight(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=incrementRight(e);
            }
        }
    }
    while(c!=(-1) && this->isEmpty(c))
    {
        c1=c;
        c=decrementLeft(c);
    }
    if(c!=(-1))
    {
        short e=this->eatWhiteDownLeft(c1);
        if(e != -1)
        {
            v.push_back(e);
            e=decrementLeft(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=decrementLeft(e);
            }
        }
    }
    while(d!=(-1) && this->isEmpty(d))
    {
        d1=d;
        d=decrementRight(d);
    }
    if(d!=(-1))
    {
        short e=this->eatWhiteDownRight(d1);
        if(e != -1)
        {
            v.push_back(e);
            e=decrementRight(e);
            while(e!=(-1) && this->isEmpty(e))
            {
                v.push_back(e);
                e=decrementRight(e);
            }
        }
    }
    return v;
}

void
Damier::performMove(short i, short j)
{/*
    set(at(i), j);
    set(EMPTY, i);*/
    _typeTr = at(i);
    set(EMPTY, i);
    set(EMPTY, j);
    _isTransition = true;
    auto src = toXY(i);
    _trSrcX = src.first;
    _trSrcY = src.second;

     auto dst = toXY(j);
    _trDestX = dst.first;
    _trDestY = dst.second;

    _transitionX = _trSrcX;
    _transitionY = _trSrcY;
}

short
Damier::performEat(short i, short j)
{
    performMove(i, j);

    _isEat = true;

    auto c1 = toXY(i);
    auto c2 = toXY(j);

    short s1 = ((c1.first > c2.first) ? -1 : 1);
    short s2 = ((c1.second > c2.second) ? -1 : 1);
    while(true)
    {
        c1.first += s1;
        c1.second += s2;
        auto s = fromXY(c1.first,c1.second);
        if(at(s) != EMPTY)
        {
            //set(EMPTY, s);
            _eatPos = s;
            return s;
        }
    }
}
void
Damier::createKings()
{
    for(int i = 0; i<_boardInfo[_board].width/2; i++)
    {
        if(tab[i] == WHITE)
        {
            tab[i] = WHITE_KING;
        }
        if(tab[_boardInfo[_board].boardSize-i-1] == BLACK)
        {
            tab[_boardInfo[_board].boardSize-i-1] = BLACK_KING;
        }
    }
}

std::vector<short>
Damier::movesOf(short x) const
{
    switch(tab[x])
    {
    case WHITE:
        return whiteManMove(x);
        //Obviously no need for break statement.
    case BLACK:
        return blackManMove(x);
    case BLACK_KING:
    case WHITE_KING:
        return kingMove(x);
    default :
        return std::vector<short>();
    }
}

std::vector<short>
Damier::eatsOf(short x)
{
    switch(at(x))
    {
    case WHITE:
        return whiteManEat(x);
        //Obviously no need for break statement.
    case BLACK:
        return blackManEat(x);
    case BLACK_KING:
        return blackKingEat(x);
    case WHITE_KING:
        return whiteKingEat(x);
    default :
        return std::vector<short>();
    }
}

std::vector<std::pair<short int, short int>>
Damier::getPossibleMoves(Player *p) const
{
    std::vector<std::pair<short int, short int>> moves;
    //Get the player's color
    Piece color = p->getColor();

    //For every entry in the board
    for(int i = 0; i < _boardInfo[_board].boardSize; i++)
    {
        short x = (short)color & at(i);
        //Check if it is the right color
        if(x != 0)
        {
            for(auto m : movesOf(i))
            {
                moves.push_back(std::make_pair(i, m));
            }
        }
    }
    return moves;
}

std::vector<std::pair<short int, short int>>
Damier::getPossibleEats(Player *p)
{
    std::vector<std::pair<short int, short int>> eats;
    //Get the player's color
    Piece color = p->getColor();

    //For every entry in the board
    for(int i = 0; i < _boardInfo[_board].boardSize; i++)
    {
        short x = (short)color & at(i);
        //Check if it is the right color
        if(x != 0)
        {
            for(auto e : eatsOf(i))
            {
                eats.push_back(std::make_pair(i, e));
            }
        }
    }
    return eats;
}

std::pair<short int, short int>
Damier::bestEatOf(short i)
{
    int maxi = 0;
    std::vector<short> eats;
    for(auto j : eatsOf(i))
    {
        //Do move.
        set(at(i), j);
        set(EMPTY, i);
        auto c1 = toXY(i);
        auto c2 = toXY(j);
        Piece eaten;
        int e;

        short s1 = ((c1.first > c2.first) ? -1 : 1);
        short s2 = ((c1.second > c2.second) ? -1 : 1);
        while(true)
        {
            c1.first += s1;
            c1.second += s2;
            e = fromXY(c1.first,c1.second);
            if(at(e) != EMPTY)
            {
                eaten = at(e);
                set(EMPTY, e);
                break;
            }
        }
        int z = maxConsecutiveEats(j);
        if(z >= maxi)
        {
            if(z > maxi)
            {
                eats.clear();
            }
            maxi = z;
            eats.push_back(j);
        }

        set(at(j), i);
        set(EMPTY, j);
        set(eaten, e);
    }
}

std::vector<std::pair<short int, short int>>
Damier::getBestPossibleEats(Player *p)
{
    std::vector<std::pair<short int, short int>> eats;
    //Get the player's color
    Piece color = p->getColor();

    int maxi = 0;
    //For every entry in the board
    for(int i = 0; i < _boardInfo[_board].boardSize; i++)
    {
        short x = (short)color & at(i);
        //Check if it is the right color
        if(x != 0)
        {
            int lclMaxi = maxConsecutiveEats(i);
            if(lclMaxi >= maxi)
            {
                if(lclMaxi > maxi)
                {
                    maxi = lclMaxi;
                    eats.clear();
                }
                for(auto j : eatsOf(i))
                {
                    //Do move.
                    set(at(i), j);
                    set(EMPTY, i);
                    auto c1 = toXY(i);
                    auto c2 = toXY(j);
                    Piece eaten;
                    int e;

                    short s1 = ((c1.first > c2.first) ? -1 : 1);
                    short s2 = ((c1.second > c2.second) ? -1 : 1);
                    while(true)
                    {
                        c1.first += s1;
                        c1.second += s2;
                        e = fromXY(c1.first,c1.second);
                        if(at(e) != EMPTY)
                        {
                            eaten = at(e);
                            set(EMPTY, e);
                            break;
                        }
                    }
                    if(maxConsecutiveEats(j) == lclMaxi - 1)
                    {
                        eats.push_back(std::make_pair(i, j));
                    }

                    set(at(j), i);
                    set(EMPTY, j);
                    set(eaten, e);
                }
            }
        }
    }
    for(auto& ps : eats)
    {
        LOG(ps.first, " --- ", ps.second, "\n");
    }

    return eats;
}

int Damier::maxConsecutiveEats(short i)
{
    auto eats = eatsOf(i);
    if(eats.empty())
    {
        return 0;
    }
    int s = 1;
    std::vector<int> maximum;
    for(auto j : eats)
    {
        //Do move.
        set(at(i), j);
        set(EMPTY, i);
        auto c1 = toXY(i);
        auto c2 = toXY(j);
        Piece eaten;
        int e;

        short s1 = ((c1.first > c2.first) ? -1 : 1);
        short s2 = ((c1.second > c2.second) ? -1 : 1);
        while(true)
        {
            c1.first += s1;
            c1.second += s2;
            e = fromXY(c1.first,c1.second);
            if(at(e) != EMPTY)
            {
                eaten = at(e);
                set(EMPTY, e);
                break;
            }
        }
        //Recursive call.
        int sx = maxConsecutiveEats(j);
        //if (sx >= s) s += sx;
        maximum.push_back(sx);

        //Undo move.
        set(at(j), i);
        set(EMPTY, j);
        set(eaten, e);
    }
    s += *std::max_element(maximum.begin(), maximum.end());
    return s;
}


std::pair<short, short>
Damier::toXY(short x) const
{
    static const short coords2dfrom1d10[][2]={{1,0}, {3,0}, {5,0}, {7,0}, {9,0},
                                              {0,1}, {2,1}, {4,1}, {6,1}, {8,1},
                                              {1,2}, {3,2}, {5,2}, {7,2}, {9,2},
                                              {0,3}, {2,3}, {4,3}, {6,3}, {8,3},
                                              {1,4}, {3,4}, {5,4}, {7,4}, {9,4},
                                              {0,5}, {2,5}, {4,5}, {6,5}, {8,5},
                                              {1,6}, {3,6}, {5,6}, {7,6}, {9,6},
                                              {0,7}, {2,7}, {4,7}, {6,7}, {8,7},
                                              {1,8}, {3,8}, {5,8}, {7,8}, {9,8},
                                              {0,9}, {2,9}, {4,9}, {6,9}, {8,9}};

    static const short coords2dfrom1d8[][2]={{1,0}, {3,0}, {5,0}, {7,0},
                                             {0,1}, {2,1}, {4,1}, {6,1},
                                             {1,2}, {3,2}, {5,2}, {7,2},
                                             {0,3}, {2,3}, {4,3}, {6,3},
                                             {1,4}, {3,4}, {5,4}, {7,4},
                                             {0,5}, {2,5}, {4,5}, {6,5},
                                             {1,6}, {3,6}, {5,6}, {7,6},
                                             {0,7}, {2,7}, {4,7}, {6,7}};

    static const short coords2dfrom1d12[][2]={{1,0}, {3,0}, {5,0}, {7,0}, {9,0}, {11,0},
                                              {0,1}, {2,1}, {4,1}, {6,1}, {8,1}, {10,1},
                                              {1,2}, {3,2}, {5,2}, {7,2}, {9,2}, {11,2},
                                              {0,3}, {2,3}, {4,3}, {6,3}, {8,3}, {10,3},
                                              {1,4}, {3,4}, {5,4}, {7,4}, {9,4}, {11,4},
                                              {0,5}, {2,5}, {4,5}, {6,5}, {8,5}, {10,5},
                                              {1,6}, {3,6}, {5,6}, {7,6}, {9,6}, {11,6},
                                              {0,7}, {2,7}, {4,7}, {6,7}, {8,7}, {10,7},
                                              {1,8}, {3,8}, {5,8}, {7,8}, {9,8}, {11,8},
                                              {0,9}, {2,9}, {4,9}, {6,9}, {8,9}, {10,9},
                                              {1,10}, {3,10}, {5,10}, {7,10}, {9,10}, {11,10},
                                              {0,11}, {2,11}, {4,11}, {6,11}, {8,11}, {10,11}};

    if(x >= _boardInfo[_board].boardSize || x < 0)
        return std::make_pair<short, short>(-1, -1);

    if(_board == 0)
        return std::make_pair(coords2dfrom1d10[x][0],coords2dfrom1d10[x][1]);
    if(_board == 1)
        return std::make_pair(coords2dfrom1d8[x][0],coords2dfrom1d8[x][1]);
    if(_board == 2)
        return std::make_pair(coords2dfrom1d12[x][0],coords2dfrom1d12[x][1]);

    return std::make_pair<short, short>(-1, -1);
}

short
Damier::fromXY(short x, short y) const
{
    static const short coords1dfrom2d10[][10] =  {{-1, 0,-1, 1,-1, 2,-1, 3,-1, 4},
                                                  { 5,-1, 6,-1, 7,-1, 8,-1, 9,-1},
                                                  {-1,10,-1,11,-1,12,-1,13,-1,14},
                                                  {15,-1,16,-1,17,-1,18,-1,19,-1},
                                                  {-1,20,-1,21,-1,22,-1,23,-1,24},
                                                  {25,-1,26,-1,27,-1,28,-1,29,-1},
                                                  {-1,30,-1,31,-1,32,-1,33,-1,34},
                                                  {35,-1,36,-1,37,-1,38,-1,39,-1},
                                                  {-1,40,-1,41,-1,42,-1,43,-1,44},
                                                  {45,-1,46,-1,47,-1,48,-1,49,-1}};

    static const short coords1dfrom2d8[][8] =   {{-1, 0,-1, 1,-1, 2,-1, 3},
                                                 { 4,-1, 5,-1, 6,-1, 7,-1},
                                                 {-1, 8,-1, 9,-1,10,-1,11},
                                                 {12,-1,13,-1,14,-1,15,-1},
                                                 {-1,16,-1,17,-1,18,-1,19},
                                                 {20,-1,21,-1,22,-1,23,-1},
                                                 {-1,24,-1,25,-1,26,-1,27},
                                                 {28,-1,29,-1,30,-1,31,-1}};

    static const short coords1dfrom2d12[][12] =  {{-1, 0,-1, 1,-1, 2,-1, 3,-1, 4,-1, 5},
                                                  { 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1},
                                                  {-1,12,-1,13,-1,14,-1,15,-1,16,-1,17},
                                                  {18,-1,19,-1,20,-1,21,-1,22,-1,23,-1},
                                                  {-1,24,-1,25,-1,26,-1,27,-1,28,-1,29},
                                                  {30,-1,31,-1,32,-1,33,-1,34,-1,35,-1},
                                                  {-1,36,-1,37,-1,38,-1,39,-1,40,-1,41},
                                                  {42,-1,43,-1,44,-1,45,-1,46,-1,47,-1},
                                                  {-1,48,-1,49,-1,50,-1,51,-1,52,-1,53},
                                                  {54,-1,55,-1,56,-1,57,-1,58,-1,59,-1},
                                                  {-1,60,-1,61,-1,62,-1,63,-1,64,-1,65},
                                                  {66,-1,67,-1,68,-1,69,-1,70,-1,71, 5}};

    if(x >= _boardInfo[_board].width || x < 0 || y >= _boardInfo[_board].width || y < 0) return -1;

    if(_board == 0) return coords1dfrom2d10[y][x];
    if(_board == 1) return coords1dfrom2d8[y][x];
    if(_board == 2) return coords1dfrom2d12[y][x];

    return -1;
}

void
Damier::draw(float x, float y, float size) const
{
    //params
    int numSamples = 20;

    glPushMatrix();
    glColor3ub(79,70,49);
    Shapes::drawRectangleFilled(x, y, size*1.02, size*1.02);
    glColor3ub(255,255,255);
    Shapes::drawRectangleFilled(x, y, size, size);

    glColor3ub(162,145,107);
    float ox = x - size*0.5f;
    float oy = y - size*0.5f;
    float dx = size/_boardInfo[_board].width;

    for(int i=0; i<_boardInfo[_board].boardSize; i++)
    {
        auto tmp = toXY(i);
        Shapes::drawRectangleFilled(ox+tmp.first*dx, oy+tmp.second*dx, dx, dx, false);
    }

    float pieceSize = size * 0.4f / _boardInfo[_board].width;
    float kingSize = size * 0.3f / _boardInfo[_board].width;

    //Draw pieces.
    ox += size*0.5f/_boardInfo[_board].width;
    oy += size*0.5f/_boardInfo[_board].width;
    for(int p=0; p<_boardInfo[_board].boardSize; p++)
    {
        auto tmp = toXY(p);
        short i = tmp.second;
        short j = tmp.first;

        switch(at(p))
        {
        case WHITE:
            glColor3ub(0xFF,0xFF,0xFF);
            Shapes::drawCircleFilled(ox+j*dx,oy+i*dx, pieceSize, numSamples);
            break;
        case BLACK:
            glColor3ub(0,0,0);
            Shapes::drawCircleFilled( ox+j*dx, oy+i*dx, pieceSize, numSamples);
            break;
        case WHITE_KING :
            glColor3ub(0xFF,0xFF,0xFF);
            Shapes::drawCircleFilled(ox+j*dx,oy+i*dx, pieceSize, numSamples);
            glColor3ub(0, 0, 0);
            Shapes::drawKing(ox+j*dx, oy+size*0.01+i*dx, -kingSize);
            break;
        case BLACK_KING :
            glColor3ub(0,0,0);
            Shapes::drawCircleFilled( ox+j*dx, oy+i*dx, pieceSize, numSamples);
            glColor3ub(0xFF, 0xFF, 0xFF);
            Shapes::drawKing(ox+j*dx, oy+0.01*size+i*dx, -kingSize);
            break;
        case EMPTY :
            break;
        }
    }

    if(_isTransition)
        switch(_typeTr)
        {
        case WHITE:
            glColor3ub(0xFF,0xFF,0xFF);
            Shapes::drawCircleFilled(ox+_transitionX*dx,oy+_transitionY*dx, pieceSize, numSamples);
            break;
        case BLACK:
            glColor3ub(0,0,0);
            Shapes::drawCircleFilled( ox+_transitionX*dx, oy+_transitionY*dx, pieceSize, numSamples);
            break;
        case WHITE_KING :
            glColor3ub(0xFF,0xFF,0xFF);
            Shapes::drawCircleFilled(ox+_transitionX*dx,oy+_transitionY*dx, pieceSize, numSamples);
            glColor3ub(0, 0, 0);
            Shapes::drawKing(ox+_transitionX*dx, oy+size*0.01+_transitionY*dx, -kingSize);
            break;
        case BLACK_KING :
            glColor3ub(0,0,0);
            Shapes::drawCircleFilled( ox+_transitionX*dx, oy+_transitionY*dx, pieceSize, numSamples);
            glColor3ub(0xFF, 0xFF, 0xFF);
            Shapes::drawKing(ox+_transitionX*dx, oy+0.01*size+_transitionY*dx, -kingSize);
            break;
        case EMPTY :
            break;
        }

    glPopMatrix();
}

void
Damier::update(int dt)
{
    if(_isTransition == false)
    {
        return;
    }
    _transitionX += (_trDestX - _trSrcX) * (float)dt * 3 / 1000.f;
    _transitionY += (_trDestY - _trSrcY) * (float)dt * 3 / 1000.f;

    if((_transitionX >= _trDestX && _transitionX >= _trSrcX) ||
        (_transitionX <= _trDestX && _transitionX <= _trSrcX))
        _transitionX = _trDestX;

    if((_transitionY >= _trDestY && _transitionY >= _trSrcY) ||
        (_transitionY <= _trDestY && _transitionY <= _trSrcY))
        _transitionY = _trDestY;

    if(_transitionX == _trDestX && _transitionY == _trDestY)
    {
        set(_typeTr,fromXY(_trDestX, _trDestY));
        set(Piece::EMPTY,fromXY(_trSrcX, _trSrcY));
        _isTransition = false;
        if(_isEat)
        {
            set(Piece::EMPTY, _eatPos);
            _isEat = false;
        }
    }
}

bool
Damier::transition()
{
    return _isTransition;
}

std::pair<float, float>
Damier::getTransitionActualPos()
{
    return std::make_pair(_transitionX, _transitionY);
}

int
Damier::getBoardWidth() const
{
    return _boardInfo[_board].width;
}

void
Damier::canEatBakward(bool b)
{
    _eatBackward = b;
}

void
Damier::canKingFly(bool b)
{
    _flyingKing = b;
}
