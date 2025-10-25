#pragma once
#include "notifyType.h"

class Observer {
public:
    virtual ~Observer() = default;

    // univerzální notify
    virtual void Notify(NotifyType type, void* data) = 0;
};
