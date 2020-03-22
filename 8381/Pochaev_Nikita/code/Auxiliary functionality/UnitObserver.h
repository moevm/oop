#ifndef OOP_UNITOBSERVER_H
#define OOP_UNITOBSERVER_H

#include <memory>

class Unit;

/**
 * Interface for the Observer (Subscriber)
 */
class UnitObserver
{
public:
    virtual void updateAfterDeath(std::shared_ptr<Unit> corpse, size_t x, size_t y) = 0;
};

#endif //OOP_UNITOBSERVER_H
