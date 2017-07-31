#pragma once

#include "Player.h"

class ComputerPlayer : public Player
{
public :
    ComputerPlayer(Damier::Piece color) : Player(color) {}
    virtual std::pair<short int, short int> makeMove(
        Damier& dam,
        std::vector<std::pair<short int, short int>>& moves) override
    {
        return moves[0];
    }
    virtual ~ComputerPlayer(){};
};


