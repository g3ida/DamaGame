#pragma once

#include "Player.h"
#include "Damier.h"
class ComputerPlayer : public Player
{
public :
    ComputerPlayer(Damier::Piece color) : Player(color) {};
    virtual std::pair<short int, short int> makeMove(
        Damier& dam,std::vector<std::pair<short int, short int>>& moves) override
    {
        if(actionVector.empty())
        {
            std::vector<Action> m,n;
            MinMax algo(dam,this,1,NULL,0,m,1);
            algo.makeTree(dam,4,4,this,enn,1,1,n);
            actionVector=n;
            std::pair<short,short> p;
            p.first=actionVector[0].from;
            p.second=actionVector[0].pos;
            actionVector.erase(actionVector.begin(),actionVector.begin()+1);
            return(p);
        }
        else
        {
            std::pair<short,short> p;
            p.first=actionVector[0].from;
            p.second=actionVector[0].pos;
            actionVector.erase(actionVector.begin(),actionVector.begin()+1);
            return(p);
        }
    }
    virtual ~ComputerPlayer(){};

private :
    std::vector <Action> actionVector;
};


