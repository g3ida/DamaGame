#include <iostream>
#include <vector>
using namespace std;
class Piece
{
    short couleur; // 1 pour blanc ; 2 pour noir
    short type; // 1 pour normal ; 2 pour double
    short emplacement; //la premiere case en haut a gauche a le numero 1. Pour simplifier, on la prend la case 0.
public :
    Piece (short c,short t,short e) : couleur(c),type(t),emplacement(e) {};
    Piece (): couleur(0),type(0),emplacement(0){};
    friend class Damier;
};
class Damier
{
    Piece* tableau;
public :
    Damier();
    void nettoyer ();
    void setpiece (short x, short couleur, short type=1);
    bool isEmpty(short x);
    bool isWhite(short x);//determination de la piece si elle est blanche (si elle existe)
    bool isNormal(short x); //determination de type de la piece
    vector<short> whiteNormalMouvement(short x);
    vector<short> blackNormalMouvement(short x);
    vector<short> whiteKingMouvement(short x);
    vector<short> blackKingMouvement(short x);

};
class Jeu
{

};


// Definition des fonctions de classes Damier
bool Damier:: isEmpty(short x)
{
    if(tableau[x].couleur==0)
        return (true);
    else
        return (false);
}
bool Damier:: isWhite(short x)
{
    if(tableau[x].couleur==1)
        return (true);
    else
        return (false);
}
bool Damier:: isNormal(short x)
{
    if(tableau[x].type==1)
        return (true);
    else
        return (false);
}
void Damier::setpiece (short x, short couleur, short type)
{
    if (this->isEmpty(x))
    {
        Piece a(couleur,type,x);
        tableau[x] =a;
    }
    else
        cout << "Emplacement non vide";
}
Damier::Damier()
{
    int i;
    for( i=0; i<20 ; i++)
    {
        Piece a(2,1,i);
        tableau[i] =a;
    }
    Piece a;
    for ( i=20 ; i<30; i++)
    {
        tableau[i]=a;
    }
    for ( i=30 ; i<50; i++)
    {
        Piece a(1,1,i);
        tableau[i]=a;
    }
}
void Damier::nettoyer()
{
    Piece a;
    for(int i=0; i<50; i++)
        tableau[i]=a;
}
short decrementRight(short x)
{
   if((x/5)==0)
        return(-1);
   else
   {
       switch (x%10==5)
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
}
short decrementLeft(short x)
{
   if((x/5)==0)
        return(-1);
   else
   {
       switch (x%10==5)
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
}
short incrementLeft(short x)
{
   if((x/5)==9)
        return(-1);
   else
   {
       switch (x%10==5)
        {
            case 5: return(-1);
                    break;
            case 4: return(x+5);
                    break;
            case 0 ...3 : return(x+5);
                            break;
            case 6 ... 9 : return(x+4);
                            break;
        }
   }
}
short incrementRight(short x)
{
   if((x/5)==9)
        return(-1);
   else
   {
       switch (x%10==5)
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
}
vector<short> Damier::whiteNormalMouvement(short x)
{
    vector<short> v;
    short a=decrementLeft(x);
    short b=decrementRight(x);
    if( (a !=(-1)) && this->isEmpty(a) )
        v.push_back(a);
    if( (b!=(-1)) && this->isEmpty(b) )
        v.push_back(b);
    return(v);
}
vector<short> Damier::blackNormalMouvement(short x)
{
    vector<short> v;
    short a=incrementLeft(x);
    short b=incrementRight(x);
    if( (a !=(-1)) && this->isEmpty(a) )
        v.push_back(a);
    if( (b!=(-1)) && this->isEmpty(b) )
        v.push_back(b);
    return(v);
}


// fin de definition de la classe Damier


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
