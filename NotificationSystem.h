#pragma once

#include "Settings.h"
#include <vector>

class NotificationListner;

class NotificationSystem
{
public:
    struct Message{
        enum class Type{
            /*Menu messages*/
            MenuNavigation, MenuValidation,
            /*Settings messages*/
            VolumeChange,
            /*Game-play messages*/
            PlayerType, TurnChange, GameMove, GameEat, ElementaryEat, PlayerWin, NilGame, ClicTerrain
            };

        struct VolumeChangeData
        {
            float level;
        };

        struct PlayerTypeData
        {
            Settings::Player player1;
            Settings::Player player2;
        };

        struct ClicTerrainData
        {
            int boardPos;
        };

        union Data
        {
            VolumeChangeData volumeChange;
            PlayerTypeData playerType;
            ClicTerrainData clicTerrain;
        };
        Type type;
        Data data;
    };
    void registerObserver(NotificationListner* obs);
    void unregisterObserver(NotificationListner* obs);
    void notifyObservers(Message& m);

    static NotificationSystem& getInstance()
    {
        static NotificationSystem sys;
        return sys;
    }

private:
    ~NotificationSystem(){};
    std::vector<NotificationListner*> _observers;
};
