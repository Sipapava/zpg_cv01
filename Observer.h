#pragma once
#include "notifyType.h"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Notify(NotifyType type, void* data) = 0;
};
