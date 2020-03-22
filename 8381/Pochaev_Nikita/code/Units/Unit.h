#ifndef OOP_UNIT_H
#define OOP_UNIT_H

#include <iostream>
#include <cstddef>
#include <string>
#include <utility>
#include <memory>
#include <map>

#include "../Information headers/unitPar.h"
#include "../Coords.h"
#include "IUnitAttack.h"
#include "../Auxiliary functionality/UnitObserver.h"
#include "../Auxiliary functionality/UnitMediators.h"
#include "../Auxiliary functionality/UnitSubject.h"

class CompositeUnit;

class Unit : public UnitSubject, public IUnitAttack, public std::enable_shared_from_this<Unit>
{
protected:
    std::string name;
    size_t health{};
    size_t armor{};
    size_t meleeAttackStrength{};
    size_t movementRange{};
    ssize_t actionTokens{};

    Coords position;
    std::shared_ptr<UnitMoveMediator> moveMediator;
    std::vector<std::shared_ptr<UnitObserver>> observers;

public:
    [[nodiscard]] virtual Unit* clone() const = 0;    // The Virtual (Copy) Constructor
    ~Unit() override = default;

    [[nodiscard]] virtual bool isAlive() const;
    [[nodiscard]] virtual size_t getHealth() const;
    [[nodiscard]] virtual size_t getArmor() const;
    [[nodiscard]] virtual size_t getMeleeAttackStrength() const;
    [[nodiscard]] size_t getActionTokens() const;
    [[nodiscard]] Coords getCoords() const;
    [[nodiscard]] size_t getMovementRange() const;
    [[nodiscard]] virtual size_t getUnitQuantity() const;
    [[nodiscard]] virtual std::map<std::string, size_t> getComposition();
    [[nodiscard]] virtual std::string getType() = 0;

    // For movement
    void move(size_t x, size_t y);
    virtual void reallocation(size_t new_x, size_t new_y);
    void setUnitMoveMediator(std::shared_ptr<UnitMoveMediator> mediator_);

    // For composite units
    virtual void addUnit(std::shared_ptr<Unit> unit);
    virtual CompositeUnit* isComposite();

    [[nodiscard]] virtual bool meleeAttack(size_t x, size_t y) const = 0;
    virtual void takeDamage(size_t damageSize);
    void setExtraActionToken();
    virtual void setMeleeAttackBoost(size_t boost);
    virtual void setArmorBoost(size_t boost);
    void disableExtraActionToken();
    virtual void describeYourself();

    // Observer functionality
    void registerObserver(std::shared_ptr<UnitObserver> observer) override;
    void removeObserver(std::shared_ptr<UnitObserver> observer) override;
    void notifyObserversAboutDeath() override;

    // Attack functionality
    void setUnitMeleeAttackMediator(std::shared_ptr<UnitMeleeAttackMediator> mediator_) override;
    void carryOutMeleeAttack(size_t x, size_t y) override;
};

#endif //OOP_UNIT_H
