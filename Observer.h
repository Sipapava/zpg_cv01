#pragma once
#include "notifyType.h"

class Observer {
public:
    virtual ~Observer() = default;

    // univerz�ln� notify
    virtual void Notify(NotifyType type, void* data) = 0;
};
