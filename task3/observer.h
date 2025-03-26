#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer);
    void notifyObservers(const std::string& message);
};

#endif 