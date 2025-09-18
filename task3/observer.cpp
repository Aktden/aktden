#include "observer.h"

void Observable::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Observable::notifyObservers(const std::string& message) {
    for (auto observer : observers) {
        observer->update(message);
    }
}