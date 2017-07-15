#include "Damier.h"
#include <GL/glut.h>
#include "Shapes.h"
#include "Log.h"

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
        tab[i] = WHITE;
        tab[50-i-1] = BLACK;
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
    if(i < 0 || i > SIZE)
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
   if((x/5)==9)
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
std::vector<short>&&
Damier::whiteNormalMouvement(short x)
{
    std::vector<short> v;
    short a=decrementLeft(x);
    short b=decrementRight(x);
    if( (a !=(-1)) && tab[a] == EMPTY)
        v.push_back(a);
    if( (b!=(-1)) && tab[a] == EMPTY )
        v.push_back(b);
    return std::move(v);
}
std::vector<short>&&
Damier::blackNormalMouvement(short x)
{
    std::vector<short> v;
    short a=incrementLeft(x);
    short b=incrementRight(x);
    if( (a !=(-1)) && tab[a] == EMPTY )
        v.push_back(a);
    if( (b!=(-1)) && tab[a] == EMPTY )
        v.push_back(b);
    return std::move(v);
}
std::vector<short>&&
Damier::kingMouvement(short x)
{
    std::vector<short> v;
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
    return std::move(v);
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

std::vector<short>&&
Damier::whiteNormalEat(short x)
{
    std::vector<short> v;
    short a=this->eatBlackDownRight(x);
    short b=this->eatBlackDownLeft(x);
    short c=this->eatBlackUpRight(x);
    short d=this->eatBlackUpLeft(x);
    if(a)
        v.push_back(a);
    if(b)
        v.push_back(b);
    if(c)
        v.push_back(c);
    if(d)
        v.push_back(d);

    return std::move(v);
}
std::vector<short>&& Damier::blackNormalEat(short x)
{
    std::vector<short> v;
    short a=this->eatWhiteUpRight(x);
    short b=this->eatWhiteUpLeft(x);
    short c=this->eatWhiteDownRight(x);
    short d=this->eatWhiteDownLeft(x);
    if(a)
        v.push_back(a);
    if(b)
        v.push_back(b);
    if(c)
        v.push_back(c);
    if(d)
        v.push_back(d);
    return std::move(v);
}
std::vector<short>&&
Damier::whiteKingEat(short x)
{
    std::vector<short> v;
    short a=incrementLeft(x);
    short b=incrementRight(x);
    short c=decrementLeft(x);
    short d=decrementRight(x);
    short a1,b1,c1,d1;
    while(a!=(-1) && this->isEmpty(a))
    {
        a1=a;
        a=incrementLeft(a); // at the end, a will take the first non empty place or -1 and a1 take the place before
    }

    if(a!=(-1))
    {
        short e=this->eatBlackUpLeft(a1);
        if(e)
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
        b=incrementRight(a);
    }
    if(b!=(-1))
    {
        short e=this->eatBlackUpRight(b1);
        if(e)
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
        if(e)
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
        if(e)
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
    return std::move(v);
}

std::vector<short>&&
Damier::blackKingEat(short x)
{
    std::vector<short> v;
    short a=incrementLeft(x);
    short b=incrementRight(x);
    short c=decrementLeft(x);
    short d=decrementRight(x);
    short a1,b1,c1,d1;
    while(a!=(-1) && this->isEmpty(a))
    {
        a1=a;
        a=incrementLeft(a); // at the end, a will take the first non empty place or -1 and a1 take the place before
    }

    if(a!=(-1))
    {
        short e=this->eatWhiteUpLeft(a1);
        if(e)
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
        b=incrementRight(a);
    }
    if(b!=(-1))
    {
        short e=this->eatWhiteUpRight(b1);
        if(e)
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
        if(e)
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
        if(e)
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
    return std::move(v);
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
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            if((i+j)%2 == 0)
                drawRectangleFilled(ox+i*dx, oy+j*dx, dx, dx, false);
        }
    }
    //Afficher les pieces
    ox += size*0.05f;
    oy += size*0.05f;
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            if((i+j)%2 == 0)
            {
                switch(tab[(i*10 + j)/2])
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
                        drawKing(ox+j*dx, oy-size*0.01+i*dx, size*0.03f);
                        break;
                    case BLACK_KING :
                        glColor3ub(0,0,0);
                        drawCircleFilled( ox+j*dx, oy+i*dx, size*0.04f, numSamples);
                        glColor3ub(0xFF, 0xFF, 0xFF);
                        drawKing(ox+j*dx, oy-0.01*size+i*dx, size*0.03f);
                        break;
                    case EMPTY :
                        break;
                }
            }
        }
    }

    glPopMatrix();
}
