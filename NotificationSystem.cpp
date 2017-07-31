#include "NotificationSystem.h"
#include "NotificationListner.h"
#include <algorithm>
#include "Logger/Log.h"

void
NotificationSystem::registerObserver(NotificationListner* obs)
{
    if(obs != nullptr)
        _observers.push_back(obs);
}

void
NotificationSystem::unregisterObserver(NotificationListner* obs)
{
    _observers.erase(std::remove(_observers.begin(), _observers.end(), obs));
}

void
NotificationSystem::notifyObservers(NotificationSystem::Message& m)
{
    for(auto o : _observers)
        o->notify(m);
}
