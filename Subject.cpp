#include "subject.h"

void subject::AddObserver(Observer* o) {
    observers.push_back(o);
}

void subject::RemoveObserver(Observer* o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void subject::NotifyObservers(NotifyType type, void* data) {
    for (Observer* o : observers) {
        o->Notify(type, data);
    }
}


void subject::NotifyObserver(Observer* o, NotifyType type, void* data) {
    if (o) {
        o->Notify(type, data);
    }
}
