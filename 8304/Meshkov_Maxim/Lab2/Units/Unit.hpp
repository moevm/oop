#pragma once

#include <string>
#include <memory>
#include <set>

class UnitFactory;
class Field;
#include "../FieldPosition.hpp"

class Unit {
public:
    virtual ~Unit() = default;

    virtual std::string getName() const = 0;

    virtual std::shared_ptr<UnitFactory> createUnitFactory() const = 0;
    virtual std::shared_ptr<Unit> createCopy() const = 0;

    virtual int getHealth() const = 0;
    virtual int getHit() const = 0;
    virtual bool icesWhenAttacks() const = 0;
    virtual int getArmor() const = 0;
    virtual int getMoveRange() const = 0;
    virtual int getAttackRange() const = 0;
    virtual bool isIced() const = 0;

    virtual void modifyHealth(int change) = 0;
    virtual void ice() = 0;

    virtual std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition, const Field &field) const = 0;
    virtual std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition, const Field &field) const = 0;

    virtual void attack(FieldPosition victimPosition, Field &field) = 0;

protected:
    Unit &operator=(const Unit&) = default;
};
