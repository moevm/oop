#ifndef OOP_UNITSUBJECT_H
#define OOP_UNITSUBJECT_H

#include <vector>
#include <algorithm>

#include "UnitObserver.h"

/**
 * Interface for the Subject (Publisher)
 */
class UnitSubject
{
public:
    /**
     * Register an observer
     * @param observer
     * the observer object to be registered
     */
    virtual void registerObserver(std::shared_ptr<UnitObserver> observer) = 0;

    /**
     * Unregister an observer
     * @param observer
     * the observer object to be unregistered
     */
    virtual void removeObserver(std::shared_ptr<UnitObserver> observer) = 0;

    /**
     * Notify all the registered observers when a change happens
     */
    virtual void notifyObserversAboutDeath() = 0;
};

#endif //OOP_UNITSUBJECT_H
