#pragma once

#include "Player.h"
#include "NotificationListner.h"
#include <map>
#include <algorithm>

#include "logger/Log.h"

class HumanPlayer : public Player, public NotificationListner
{
public :
    HumanPlayer(Damier::Piece color) : Player(color)
    {
        _clicPos = std::make_pair(-1, -1);

        NotificationSystem::getInstance().registerObserver(this);
    }
    virtual std::pair<short int, short int> makeMove(
        Damier& dam,
        std::vector<std::pair<short int, short int>>& moves) override
    {
        if(_clicPos.first != -1 && _clicPos.second != -1)
        {
            if(std::find(moves.begin(), moves.end(), _clicPos) != moves.end())
            {
                auto tmp = _clicPos;
                _clicPos.first = -1;
                _clicPos.second = -1;
                return tmp;
            }
        }
        else if(_clicPos.first != -1)
        {
            bool found = false;
            for(auto& p : moves)
            {
                if(p.first == _clicPos.first)
                {
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                _clicPos.first = -1;
            }
        }
        return std::make_pair(-1, -1);
    }

    virtual void notify(NotificationSystem::Message& m)
    {
        if(m.type == NotificationSystem::Message::Type::ClicTerrain)
        {
            if(_clicPos.first == -1)
            {
                _clicPos.first = m.data.clicTerrain.boardPos;
            }
            else if(_clicPos.second == -1)
            {
                _clicPos.second = m.data.clicTerrain.boardPos;
            }
            else
            {
                 _clicPos.first = m.data.clicTerrain.boardPos;
                 _clicPos.second = -1;
            }
        }
    }

    virtual ~HumanPlayer()
    {
        NotificationSystem::getInstance().unregisterObserver(this);
    }
private:
    std::pair<short int, short int> _clicPos;
};


