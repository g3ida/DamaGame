#include "Damier.h"
#include <GL/glut.h>
#include "Shapes.h"
#include "Log.h"
#include "Player.h"
#include <functional>

Damier::Damier()
{
    reset();
}

void
Damier::clear()
{
    for(int i=0; i<SIZE; i++)
        tab[i] = EMPTY;
}

void
Damier::reset()
{
    clear();
    for(int i=0; i<20; i++)
    {
        tab[i] = BLACK;
        tab[50-i-1] = WHITE;
    }
}

void
Damier::set(Piece p, int i)
{
    if(i < 0 || i > SIZE)
        return;

    tab[i] = p;

}

Damier::Piece
Damier::at(int i)
{
    if(i < 0 || i >= SIZE)
        return EMPTY;

    return tab[i];
}
bool Damier::isEmpty(short x)
{
    return (at(x) == EMPTY);
}
bool Damier::isWhite(short x)
{
    return (at(x) == WHITE || at(x) == WHITE_KING);

}
short decrementRight(short x)
{
   if((x/5)==0)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(x-5);
                    break;
            case 4: return(-1);
                    break;
            case 0 ... 3 : return(x-4);
                            break;
            case 6 ... 9 : return(x-5);
                            break;
        }
   }
   return -1;
}

static short decrementLeft(short x)
{
   if((x/5)==0)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(-1);
                    break;
            case 4: return(x-5);
                    break;
            case 0 ... 3 : return(x-5);
                            break;
            case 6 ... 9 : return(x-6);
                            break;
        }
   }
   return -1;
}
static short incrementLeft(short x)
{
   if(x >= 45)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(-1);
                    break;
            case 4: return(x+5);
                    break;
            case 0 ... 3 : return(x+5);
                            break;
            case 6 ... 9 : return(x+4);
                            break;
        }
   }
   return -1;
}
static short incrementRight(short x)
{
   if((x/5)==9)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(x+5);
                    break;
            case 4: return(-1);
                    break;
            case 0 ... 3 : return(x+6);
                            break;
            case 6 ... 9 : return(x+5);
                            break;
        }
   }
   return(-1);
}
std::vector<short>
Damier::whiteManMove(short x)
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
Damier::blackManMove(short x)
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
Damier::kingMove(short x)
{
    std::vector<short> v;

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

short Damier::eatBlackDownLeft(short x)
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
short Damier::eatBlackDownRight(short x)
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
short Damier::eatWhiteDownRight(short x)
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
short Damier::eatWhiteDownLeft(short x)
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
short Damier::eatWhiteUpLeft(short x)
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
short Damier::eatWhiteUpRight(short x)
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
short Damier::eatBlackUpLeft(short x)
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
short Damier::eatBlackUpRight(short x)
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
Damier::whiteManEat(short x)
{
    std::vector<short> v;
    short a=this->eatBlackDownRight(x);
    short b=this->eatBlackDownLeft(x);
    short c=this->eatBlackUpRight(x);
    short d=this->eatBlackUpLeft(x);
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
std::vector<short> Damier::blackManEat(short x)
{
    std::vector<short> v;
    short a=this->eatWhiteUpRight(x);
    short b=this->eatWhiteUpLeft(x);
    short c=this->eatWhiteDownRight(x);
    short d=this->eatWhiteDownLeft(x);
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
            e=incrementLeft(e);
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
            e=incrementLeft(e);
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
    if(v.empty())
    {
        LOG("king at", x, " cannot eat\n");
    }
    return v;
}

void
Damier::performMove(short i, short j)
{
    tab[j] = tab[i];
    tab[i] = EMPTY;
}

short
Damier::performEat(short i, short j)
{
    set(at(i), j);
    set(EMPTY, i);

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
            set(EMPTY, s);
            return s;
        }
    }
}
void
Damier::createKings()
{
    for(int i = 0; i<5; i++)
    {
        if(tab[i] == WHITE)
        {
            tab[i] = WHITE_KING;
        }
        if(tab[SIZE-i-1] == BLACK)
        {
            tab[SIZE-i-1] = BLACK_KING;
        }
    }
}

std::vector<short>
Damier::movesOf(short x)
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
Damier::getPossibleMoves(Player *p)
{
    std::vector<std::pair<short int, short int>> moves;
    //Get the player's color
    Piece color = p->getColor();

    //For every entry in the board
    for(int i = 0; i < 50; i++)
    {
        short x = (short)color & tab[i];
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
    for(int i = 0; i < 50; i++)
    {
        short x = (short)color & tab[i];
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

std::pair<short, short>
Damier::toXY(short x)
{
    static const short coords2dfrom1d[][2]={{1,0}, {3,0}, {5,0}, {7,0}, {9,0},
                                            {0,1}, {2,1}, {4,1}, {6,1}, {8,1},
                                            {1,2}, {3,2}, {5,2}, {7,2}, {9,2},
                                            {0,3}, {2,3}, {4,3}, {6,3}, {8,3},
                                            {1,4}, {3,4}, {5,4}, {7,4}, {9,4},
                                            {0,5}, {2,5}, {4,5}, {6,5}, {8,5},
                                            {1,6}, {3,6}, {5,6}, {7,6}, {9,6},
                                            {0,7}, {2,7}, {4,7}, {6,7}, {8,7},
                                            {1,8}, {3,8}, {5,8}, {7,8}, {9,8},
                                            {0,9}, {2,9}, {4,9}, {6,9}, {8,9}};
    if(x > 49 || x < 0)
        return std::make_pair<short, short>(-1, -1);

    return std::make_pair(coords2dfrom1d[x][0],coords2dfrom1d[x][1]);

}

short
Damier::fromXY(short x, short y)
{
    static const short coords1dfrom2d[][10] =  {{-1, 0,-1, 1,-1, 2,-1, 3,-1, 4},
                                                { 5,-1, 6,-1, 7,-1, 8,-1, 9,-1},
                                                {-1,10,-1,11,-1,12,-1,13,-1,14},
                                                {15,-1,16,-1,17,-1,18,-1,19,-1},
                                                {-1,20,-1,21,-1,22,-1,23,-1,24},
                                                {25,-1,26,-1,27,-1,28,-1,29,-1},
                                                {-1,30,-1,31,-1,32,-1,33,-1,34},
                                                {35,-1,36,-1,37,-1,38,-1,39,-1},
                                                {-1,40,-1,41,-1,42,-1,43,-1,44},
                                                {45,-1,46,-1,47,-1,48,-1,49,-1}};
    if(x > 9 || x < 0 || y > 9 || y < 0) return -1;
    return coords1dfrom2d[y][x];
}

void
Damier::draw(float x, float y, float size)
{
    //params
    int numSamples = 20;

    glPushMatrix();
    glColor3ub(79,70,49);
    drawRectangleFilled(x, y, size*1.02, size*1.02);
    glColor3ub(255,255,255);
    drawRectangleFilled(x, y, size, size);

    glColor3ub(162,145,107);
    float ox = x - size*0.5f;
    float oy = y - size*0.5f;
    float dx = size/10.f;

    for(int i=0; i<50; i++)
    {
        auto tmp = toXY(i);
        drawRectangleFilled(ox+tmp.first*dx, oy+tmp.second*dx, dx, dx, false);
    }

    //Draw pieces.
    ox += size*0.05f;
    oy += size*0.05f;
    for(int p=0; p<50; p++)
    {
        auto tmp = toXY(p);
        short i = tmp.second;
        short j = tmp.first;

        switch(tab[p])
        {
        case WHITE:
            glColor3ub(0xFF,0xFF,0xFF);
            drawCircleFilled(ox+j*dx,oy+i*dx, size*0.04f, numSamples);
            break;
        case BLACK:
            glColor3ub(0,0,0);
            drawCircleFilled( ox+j*dx, oy+i*dx, size*0.04f, numSamples);
            break;
        case WHITE_KING :
            glColor3ub(0xFF,0xFF,0xFF);
            drawCircleFilled(ox+j*dx,oy+i*dx, size*0.04f, numSamples);
            glColor3ub(0, 0, 0);
            drawKing(ox+j*dx, oy+size*0.01+i*dx, -size*0.03f);
            break;
        case BLACK_KING :
            glColor3ub(0,0,0);
            drawCircleFilled( ox+j*dx, oy+i*dx, size*0.04f, numSamples);
            glColor3ub(0xFF, 0xFF, 0xFF);
            drawKing(ox+j*dx, oy+0.01*size+i*dx, -size*0.03f);
            break;
        case EMPTY :
            break;
        }
    }
    glPopMatrix();
}
