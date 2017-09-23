#include "Damier.h"
#include <GL/glut.h>
#include "Shapes.h"
#include "logger/Log.h"
#include "Player.h"
#include <functional>
#include "Settings.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
using namespace std;
int const N= 500;//52.8903;
int const K= 1000;//110;
int const S= 5.0709;
int const T= 5.1219;
int const A= 5.1419;
float const fmax = std::numeric_limits<float>::max();
float const fmin = -fmax;

nbWhite(Damier &d)
{
    int nb=0;
     for(int l=0;l<50;l++)
    {
        if(d.at(l)==Damier::WHITE)
            nb++;

        if(d.at(l)==Damier::WHITE_KING)
            nb++;
    }
    return(nb);
}
nbBlack(Damier &d)
{
    int nb=0;
     for(int l=0;l<50;l++)
    {
        if(d.at(l)==Damier::BLACK)
            nb++;

        if(d.at(l)==Damier::BLACK_KING)
            nb++;
    }
    return(nb);
}
pair<int,int> AttachedPieces(Damier &d)
{
    int k=0 , p=0;
    for(int i=0; i<45;i++)
    {
        if(d.isWhite(i))
        {
            if(d.isWhite(d.incrementLeft(i)))
                k++;
            if(d.isWhite(d.incrementRight(i)))
               k++;
        }
        else
        {
            if(!d.isEmpty(i))
            {
                if(!(d.isWhite(d.incrementLeft(i))) && !(d.isEmpty(d.incrementLeft(i))))
                    p++;
                if(!(d.isWhite(d.incrementRight(i))) && !(d.isEmpty(d.incrementRight(i))))
                   p++;
            }
        }
    }
    pair<int,int> a(k,p);
    return(a);
}
float MinMax::calculGain(Damier &d,Player* p,int playNumber)
{
    float Gain =0;
    Damier::Piece color = p->getColor();
    int nbBlck=nbBlack(d);
    int nbWhte=nbWhite(d);
    /*if(moves.empty())
        return(-fmax)
    else;*/
    {
        if(((nbWhite(d)==0) && (color==Damier::Piece::BLACK)) || ((nbBlack(d)==0) && (color==Damier::Piece::WHITE)))
            return(fmax);
    }
   for(int i=0;i<this->moves.size();i++)
   {
        if(moves[i].type=='x')
        {
            if((this->moves[i].couleur)==Damier::WHITE)
                Gain-=N*nbBlck;
            else
            {
                if((this->moves[i].couleur)==Damier::WHITE_KING)
                    Gain-=K*nbBlck;
                else
                {
                    if((this->moves[i].couleur)==Damier::BLACK)
                        Gain+=N*nbWhte;
                    else
                        Gain+=K*nbWhte;
                }
            }
        }
   }
   for(int i=0;i<50;i++)
   {
         if(d.at(i)==Damier::WHITE)
            Gain+=N;
         if(d.at(i)==Damier::WHITE_KING)
                Gain+=K;
         if(d.at(i)==Damier::BLACK)
            Gain-=N;
         if(d.at(i)==Damier::BLACK_KING)
            Gain-=K;

   }
   for(int l=20; l<30; l++)
    {
        if(d.at(l)==Damier::WHITE)
            Gain+=S*(nbWhte+nbBlck);
        if(d.at(l)==Damier::WHITE_KING)
            Gain+=S*(nbWhte+nbBlck);
        if(d.at(l)==Damier::BLACK)
            Gain-=S*(nbWhte+nbBlck);
        if(d.at(l)==Damier::BLACK_KING)
            Gain-=S*(nbWhte+nbBlck);
    }
    /*for(int l=0;l<5;l++)
    {
        if(d.at(l)==Damier::BLACK)
                Gain-=T/playNumber;
        if(d.at(l)==Damier::BLACK_KING)
                Gain-=T/playNumber;
    }
    for(int l=45; l<50;l++)
    {
        if(d.at(l)==Damier::WHITE)
            Gain+=T/playNumber;
        if(d.at(l)==Damier::WHITE_KING)
            Gain+=T/playNumber;
    }*/
    Gain+= (AttachedPieces(d).first)*A;
    Gain-= (AttachedPieces(d).second)*A;
    if(color == Damier::BLACK)
        Gain= -Gain;
    return(Gain);
}
/*float calGain(Damier &d,int playNumber,std::vector<Action> moves)
{
    float Gain =0;
    int nbBlck=nbBlack(d);
    int nbWhte=nbWhite(d);
   for(int i=0;i<moves.size();i++)
   {
        if(moves[i].type=='x')
        {
            if((moves[i].couleur)==Damier::WHITE)
                Gain-=N*nbBlck;
            else
            {
                if((moves[i].couleur)==Damier::WHITE_KING)
                    Gain-=K*nbBlck;
                else
                {
                    if((moves[i].couleur)==Damier::BLACK)
                        Gain+=N*nbWhte;
                    else
                        Gain+=K*nbWhte;
                }
            }
        }
   }
   for(int i=0;i<50;i++)
   {
         if(d.at(i)==Damier::WHITE)
            Gain+=N;
         if(d.at(i)==Damier::WHITE_KING)
                Gain+=K;
         if(d.at(i)==Damier::BLACK)
            Gain-=N;
         if(d.at(i)==Damier::BLACK_KING)
            Gain-=K;

   }
   for(int l=20; l<30; l++)
    {
        if(d.at(l)==Damier::WHITE)
            Gain+=S*(nbWhte+nbBlck);
        if(d.at(l)==Damier::WHITE_KING)
            Gain+=S*(nbWhte+nbBlck);
        if(d.at(l)==Damier::BLACK)
            Gain-=S*(nbWhte+nbBlck);
        if(d.at(l)==Damier::BLACK_KING)
            Gain-=S*(nbWhte+nbBlck);
    }
    /*for(int l=0;l<5;l++)
    {
        if(d.at(l)==Damier::BLACK)
                Gain-=T/playNumber;
        if(d.at(l)==Damier::BLACK_KING)
                Gain-=T/playNumber;
    }
    for(int l=45; l<50;l++)
    {
        if(d.at(l)==Damier::WHITE)
            Gain+=T/playNumber;
        if(d.at(l)==Damier::WHITE_KING)
            Gain+=T/playNumber;
    }
    Gain+= (AttachedPieces(d).first)*A;
    Gain-= (AttachedPieces(d).second)*A;
    return(Gain);
}*/
void
MinMax::makeTree (Damier &d, int k, Player* player1 ,Player* player2,int playNumber,int playerNumber)
{
    if(k!=0)
    {
        /*if(nextMoves.empty())
        {

        }
        else*/
        if(k==1)
        {
            LOG("First move of this set is :from : ", moves[0].from, "- pos : ", moves[0].pos, " eatpos", moves[0].eatPos ,"est : ",gain,"\n");
        }
        {
        std::vector<std::vector<Action>> v=d.getBestThing(player1);
        for(int i=0;i<v.size();i++)
        {
            MinMax a(d,player1,playNumber,this,gain,v[i],playerNumber);
            nextMoves.push_back(a);
            nextMoves[i].makeTree(d,k-1,player2,player1, playNumber+1,(playerNumber%2)+1);
            //cout<<" Gain: "<<gain <<"\n";
                d.undoTheAction(v[i]);
            }

        }
    }
    else
    {
       // LOG("\n Gain pour cette coup ","from : ", moves[0].from, "- pos : ", moves[0].pos, " eatpos", moves[0].eatPos ,"est : ",gain,"\n");
    }
}
std::pair<float,float> MinMax::parcours(float& minim, float& maxim)
{
    if(nextMoves.empty())
    {
        if(gain>maxim)
            maxim=gain;
        if(minim>gain)
            minim=gain;
    }
    else
    {
        for(int i=0; i<nextMoves.size();i++)
        {
            std::pair<float,float> a=nextMoves[i].parcours(minim,maxim);
            if(a.first< minim)
                minim=a.first;
            if(a.second>maxim)
                maxim=a.second;
        }
    }
    std::pair<float,float> b(minim,maxim);
    return(b);
}
std::vector<Action> MinMax::bestPlay()
{
    float minim=fmin, b=fmin;
    float maxim=fmax, a=fmax;
    int resMin=0,resMax=0;
    for(int i=0;i<nextMoves.size();i++)
    {
        nextMoves[i].parcours(a,b);
        if(a>minim)
        {
            minim=a;
            resMin=i;
        }
        if(b>maxim)
        {
            maxim=b;
            resMax=i;
        }
        b=fmin;
        a=fmax;
    }
    if(minim==fmin)
        return(nextMoves[resMax].moves);
    else
        return(nextMoves[resMin].moves);
}
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
/*
    tab[28] = BLACK;
    tab[29] = WHITE;
    tab[18] = BLACK;*/
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

    short a=incrementLeft(x);
    short b=incrementRight(x);
    short c=decrementLeft(x);
    short d=decrementRight(x);

    while(a != (-1) && (this->isEmpty(a)))
    {
        v.push_back(a);
        a= incrementLeft(a);
    }
    while(b != (-1) && (this->isEmpty(b)))
    {
        v.push_back(b);
        b= incrementRight(b);
    }
    while(c != (-1) && (this->isEmpty(c)))
    {
        v.push_back(c);
        c= decrementLeft(c);
    }
    while(d != (-1) && (this->isEmpty(d)))
    {
        v.push_back(d);
        d= decrementRight(d);
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
    LOG("IS FLYING ? \n");
    if(!_flyingKing)
    {
        LOG("yess \n");
        auto tmp = _eatBackward;
        _eatBackward = true;
        v = whiteManEat(x);
        _eatBackward = tmp;
        return v;
    }
        LOG("No \n");

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
{
/*    set(at(i), j);
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

void
Damier::performEatA(Action a)
{
    set(at(a.from), a.pos);
    set(EMPTY, a.from) ;
    set(EMPTY,a.eatPos );
}
void
Damier::undoEat(Action a)
{
    set(at(a.pos), a.from);
    set(EMPTY, a.pos) ;
    set(a.couleur,a.eatPos);
}

void
Damier::recursive(Player *p,std::vector<Action>& retour,int n, int f,std::vector<std::vector<Action>>& res)
{
    std::vector<Action> eatA;

    std::vector<std::pair<short,short>> eat;

    eat=getBestPossibleEats(p);

    for(auto& x : eat)
    {

        auto c1 = toXY(x.first);
        auto c2 = toXY(x.second);
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
                break;
            }
        }
        Action a = Action::createEat(x.first, x.second, e, eaten);
        eatA.push_back(a);
    }
    if(n!= f)
    {
        for(int i=0;i<eatA.size();i++)
        {
            performEatA(eatA[i]);
            retour[n]=eatA[i];
            recursive(p,retour,n+1,f, res);
            undoEat(eatA[i]);
        }
    }
    else
    {
        if( n != 0)
        {
            //retour[n]=eatA[n];
            res.push_back(retour);
        }
    }
}
std::vector<std::vector<Action>>
Damier::getBestEatAction(Player *p)
{
    int var=0;
    std::vector<std::vector<Action>> res;
    Piece color = p->getColor();
    int maxi = 0;
    int n=0;
    for(int i = 0; i < _boardInfo[_board].boardSize; i++)
    {
        short x = (short)color & at(i);
        //Check if it is the right color
        if(x != 0)
        {
            int lclMaxi = maxConsecutiveEats(i);
            if(lclMaxi > maxi)
                {
                    maxi = lclMaxi;
                }
        }
    }
    std::vector<Action> retour(maxi);

    recursive(p,retour,n,maxi,res);

    for(int i=0; i<res.size();i++)
    {
        bool tr =true;
        var= res[i][0].pos;
        for(int j=1;j<res[i].size();j++)
        {
            if (var!= res[i][j].from)
                tr=false;
            var= res[i][j].pos;
        }
        if(!tr)
            res.erase(res.begin()+i);
    }
    return(res);

}
void
Damier::recursive1(Player *p,std::vector<Action>& previous,std::vector<std::vector<Action>>& res)
{
    std::vector<Action> eatA,newElement;
    newElement=previous;
    std::vector<std::pair<short,short>> eat;
    eat=getBestPossibleEats(p);
    for(auto& x : eat)
    {
        auto c1 = toXY(x.first);
        auto c2 = toXY(x.second);
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
                break;
            }
        }
        Action a = Action::createEat(x.first, x.second, e, eaten);
        eatA.push_back(a);
    }
    if(!eatA.empty())
    {
        int i;
        for(i=0;i<eatA.size();i++)
        {
            newElement.push_back(eatA[i]);
            res.push_back(newElement);
            performEatA(eatA[i]);
            recursive1(p,newElement,res);
            undoEat(eatA[i]);
        }
    }
}
std::vector<std::vector<Action>>
Damier::getAllEatAction(Player *p)
{
    int var=0;
    std::vector<std::vector<Action>> res;
    std::vector<Action> previous;
    recursive1(p,previous,res);
    for(int i=0; i<res.size();i++)
    {
        bool tr =true;
        var= res[i][0].pos;
        for(int j=1;j<res[i].size();j++)
        {
            if (var!= res[i][j].from)
                tr=false;
            var= res[i][j].pos;
        }
        if(!tr)
            res.erase(res.begin()+i);
    }
    return(res);
}
std::vector<std::vector<Action>>
Damier::getPossibleMovesA(Player *p) const
{
    Piece color = p->getColor();
    std::vector<std::vector<Action>> res;
    for(int i = 0; i < _boardInfo[_board].boardSize; i++)
    {
        short x = (short)color & at(i);
        if(x != 0)
        {
            for(auto m : movesOf(i))
            {
                std::vector<Action> moves;
                Action a = Action::createMove(i,m);
                moves.push_back(a);
                res.push_back(moves);
            }
        }
    }
    return res;
}

std::vector<std::vector<Action>>
Damier::getBestThing(Player* p)
{
    std::vector<std::vector<Action>> x;
    if(!Settings::mustEatMaxPieces())
    {
        x=getAllEatAction(p);
    }
    else
    {
        x=getBestEatAction(p);

    }

    if(x.empty())
    {
        x = getPossibleMovesA(p);
    }
    return x;
}

/*
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
*/
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

    //Draw highlighted.
    glColor4f(1.f, 1.f, 0.f, 0.3f);
    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
    for(auto h : _highlighted)
    {
        auto tmp = toXY(h);
        Shapes::drawRectangleFilled(ox+tmp.first*dx, oy+tmp.second*dx, dx, dx, false);
    }
    //glDisable(GL_BLEND);

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

void
Damier::highlight(short x)
{
    if(x < 0 || x > _boardInfo[_board].boardSize) return;
    if(std::find(_highlighted.begin(), _highlighted.end(), x) == _highlighted.end())
        _highlighted.push_back(x);
}

void
Damier::unhighlightAll()
{
    _highlighted.clear();
}
void
Damier::performAction(vector<Action> moves)
{
    for(int i=0; i<moves.size(); i++)
    {
        if(moves[i].eatPos==-1)
        {
            set(at(moves[i].from), moves[i].pos);
            set(EMPTY, moves[i].from) ;
        }
        else
        {
            performEatA(moves[i]);
        }
    }
}
void
Damier::undoTheAction(vector <Action> moves)
{
    for(int i=0; i<moves.size(); i++)
    {
        if(moves[moves.size()-i-1].eatPos==-1)
        {
            set(at(moves[moves.size()-i-1].pos), moves[moves.size()-i-1].from);
            set(EMPTY, moves[moves.size()-i-1].pos) ;
        }
        else
        {
            undoEat(moves[moves.size()-i-1]);
        }
    }
}
