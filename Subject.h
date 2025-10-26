#pragma once
#include "observer.h"
#include <vector>
#include "notifyType.h"
#include <algorithm> // pro std::remove

class Subject {
protected:
    std::vector<Observer*> observers;

public:
    virtual ~Subject() = default;

    virtual void AddObserver(Observer* o);
    virtual void RemoveObserver(Observer* o);

protected:
    
    void NotifyObservers(NotifyType type, void* data);
    void NotifyObserver(Observer* o, NotifyType type, void* data);
};


