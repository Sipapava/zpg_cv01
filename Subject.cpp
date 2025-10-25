#include "Subject.h"

void Subject::AddObserver(Observer* o) {
    observers.push_back(o);
}

void Subject::RemoveObserver(Observer* o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Subject::NotifyObservers(NotifyType type, void* data) {
    for (Observer* o : observers) {
        o->Notify(type, data);
    }
}


void Subject::NotifyObserver(Observer* o, NotifyType type, void* data) {
    if (o) {
        o->Notify(type, data);
    }
}
