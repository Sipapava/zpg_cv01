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
    // univerzální notify
    void NotifyObservers(NotifyType type, void* data);
    void NotifyObserver(Observer* o, NotifyType type, void* data);
};


//rotace udelat ttridu co dedi z rotate bude se to jmenvat treba rotace kolem obecneho bodu
//ta orovede translaci ritaci a translaci
//bude to tedz jeden objekt transformation


//notify by mel but obecny to znaema predame enum a subject, a on si pak pozna co to je a udelame chovani
//jaky je rozdil mezi C++ a osttanimi progra, jazyky z poheldu dedicnosti, v C++ je vicenasobna dedicnost