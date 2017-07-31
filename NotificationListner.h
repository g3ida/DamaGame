#pragma once

#include "NotificationSystem.h"

class NotificationListner
{
public:
    virtual void notify(NotificationSystem::Message& m) = 0;
    virtual ~NotificationListner(){};
};
