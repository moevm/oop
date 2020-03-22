#include <stdexcept>
#include "Unit.h"
#include "../Auxiliary functionality/TextColoring.h"

bool Unit::isAlive() const
{
    return health > 0;
}

size_t Unit::getHealth() const
{
    return health;
}

size_t Unit::getArmor() const
{
    return armor;
}

size_t Unit::getMeleeAttackStrength() const
{
    return meleeAttackStrength;
}

size_t Unit::getActionTokens() const
{
    return actionTokens;
}

Coords Unit::getCoords() const
{
    return position;
}

size_t Unit::getMovementRange() const
{
    return movementRange;
}

[[nodiscard]] size_t Unit::getUnitQuantity() const
{
    return 1;
}

void Unit::move(size_t x, size_t y)
{
    moveMediator->Notify(shared_from_this(), x, y);
}

void Unit::reallocation(size_t new_x, size_t new_y)
{
    position.x = new_x;
    position.y = new_y;
}

void Unit::setUnitMoveMediator(std::shared_ptr<UnitMoveMediator> mediator_)
{
    moveMediator = std::move(mediator_);
};

CompositeUnit* Unit::isComposite()
{
    return nullptr;
}

void Unit::addUnit(std::shared_ptr<Unit> unit)
{
    throw std::invalid_argument("Unable to add new unit to single");
}

void Unit::describeYourself()
{
    std::cout << "Health: " << health << std::endl;
    std::cout << "Armor: " << armor << std::endl;
    std::cout << "Melee attack strength: " << meleeAttackStrength << std::endl;
    std::cout << "Position: X = " << position.x << "; Y = " << position.y << std::endl;
    std::cout << std::endl;
}

void Unit::registerObserver(std::shared_ptr<UnitObserver> observer)
{
    observers.push_back(observer);
}

void Unit::removeObserver(std::shared_ptr<UnitObserver> observer)
{
    // find the observer
    auto iterator = std::find(observers.begin(), observers.end(), observer);

    if (iterator != observers.end())    // observer found
    {
        observers.erase(iterator);      // remove the observer
    }
}

void Unit::notifyObserversAboutDeath()
{
    for (const auto &observer : observers) // notify all observers
    {
        observer->updateAfterDeath(shared_from_this(), position.x, position.y);
    }
}

std::map<std::string, size_t> Unit::getComposition()
{
    std::map<std::string, size_t> result;
    result.insert(std::make_pair<std::string, size_t>(getType(), 1));

    return result;
}

void Unit::takeDamage(size_t damageSize)
{
    if(armor >= damageSize)
    {
        armor -= damageSize;
        return;
    }
    else
    {
        damageSize -= armor;
        armor = 0;
        if(health > damageSize)
        {
            health -= damageSize;
            return;
        }
        else
        {
            health = 0;
            notifyObserversAboutDeath();
        }
    }
}

void Unit::setExtraActionToken()
{
    actionTokens++;
}

void Unit::disableExtraActionToken()
{
    actionTokens--;
}

void Unit::setMeleeAttackBoost(size_t boost)
{
    meleeAttackStrength += boost;
}

void Unit::setArmorBoost(size_t boost)
{
    armor += boost;
}

void Unit::carryOutMeleeAttack(size_t x, size_t y)
{
    meleeAttackMediator->Notify(shared_from_this(), x, y);
}

void Unit::setUnitMeleeAttackMediator(std::shared_ptr<UnitMeleeAttackMediator> mediator_)
{
    meleeAttackMediator = std::move(mediator_);
}
