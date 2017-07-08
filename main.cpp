#include <iostream>

using namespace std;
class Piece
{
    short couleur; // 1 pour blanc ; 2 pour noir
    short type; // 1 pour normal ; 2 pour double
    short posLateral; // position lateral (defini dans la damier par des lettres)
    short posVertical; //position vertical
public :
    Piece (short c,short t,short pL,short pV) : couleur(c),type(t),posLateral(pL), posVertical(pV){};
    Piece (): couleur(0),type(0),posLateral(0),posVertical(0){};
    deplacer();
};
class Damier
{
    Piece** tableau;
public :
    Damier();
    bool isEmpty(short x, short y);
    bool isWhite(short x, short y);//determination de la piece si elle est blanche (si elle existe)
    bool isNormal(short x, short y); //determination de type de la piece
};
class Jeu
{

};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
