#ifndef OOP_UNIT_H
#define OOP_UNIT_H

#include <iostream>
#include <cstddef>
#include <string>
#include <utility>
#include <memory>
#include <map>

#include "InformationHeaders/unitPar.h"
#include "GameField/Coords.h"
#include "IUnitAttack.h"
#include "AuxiliaryFunctionality/UnitObserver.h"
#include "AuxiliaryFunctionality/UnitMediators.h"
#include "AuxiliaryFunctionality/UnitSubject.h"
#include "Game/Saving/SaveStuctures.h"

class CompositeUnit;

class Unit : public UnitSubject, public IUnitAttack, public std::enable_shared_from_this<Unit>
{
protected:
    std::string name;
    size_t health{};
    size_t armor{};
    size_t meleeAttackStrength{};
    size_t movementRange{};
    size_t actionTokens{};

    Coords position;
    Coords baseCreationPosition{};  // for restoring from memento
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
    [[nodiscard]] virtual std::map<eUnitsType, size_t> getComposition();
    [[nodiscard]] virtual eUnitsType getType() = 0;

    // For movement
    void move(size_t x, size_t y);
    virtual void reallocation(size_t new_x, size_t new_y);
    void setUnitMoveMediator(std::shared_ptr<UnitMoveMediator> mediator_);

    // For composite units
    virtual void addUnit(std::shared_ptr<Unit> unit);
    virtual CompositeUnit* isComposite();

    virtual void takeDamage(size_t damageSize);
    void setExtraActionToken();
    virtual void setMeleeAttackBoost(size_t boost);
    virtual void setArmorBoost(size_t boost);
    void disableExtraActionToken();
    virtual void describeYourself();
    virtual std::string getUnitInf() = 0;

    // Observer functionality
    void registerObserver(std::shared_ptr<UnitObserver> observer) override;
    void removeObserver(std::shared_ptr<UnitObserver> observer) override;
    void notifyObserversAboutDeath() override;

    // Attack functionality
    void setUnitMeleeAttackMediator(std::shared_ptr<UnitMeleeAttackMediator> mediator_) override;
    void carryOutMeleeAttack(size_t x, size_t y) override;

    // Memento functionality
    std::shared_ptr<UnitParametersMemento> createMemento();
    void restoreMemento(std::shared_ptr<UnitParametersMemento> memento);

    // special functionality
    static std::string convertEnumUnitNameToStr(eUnitsType type);

    // for restoring from memento
    void setBaseCreationCoords(Coords coords);
    Coords getBaseCreationCoords();
};

#endif //OOP_UNIT_H
