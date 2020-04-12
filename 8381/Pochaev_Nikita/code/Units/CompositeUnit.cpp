#include <iostream>
#include "CompositeUnit.h"
#include "AuxiliaryFunctionality/TextColoring.h"

size_t CompositeUnit::getHealth() const
{
    size_t total = 0;
    for(const auto & unit : units)
    {
        total += unit->getMeleeAttackStrength();
    }

    return total;
}

size_t CompositeUnit::getArmor() const
{
    size_t total = 0;
    for(const auto & unit : units)
    {
        total += unit->getArmor();
    }
    return total;
}

size_t CompositeUnit::getMeleeAttackStrength() const
{
    size_t total = 0;
    for(const auto & unit : units)
    {
        total += unit->getMeleeAttackStrength();
    }

    return total;
}

void CompositeUnit::describeYourself()
{
    std::cout << ANSIColor::coloredString("I'm composite unit!", ANSIColor::FG_GREEN) << std::endl;
    std::cout << "Position: X = " << position.x << "; Y = " << position.y << std::endl;
    std::cout << "Includes:" << std::endl << std::endl;
    for(auto const& instance : units)
    {
        instance->describeYourself();
    }
}

std::string CompositeUnit::getUnitInf()
{
    std::string result;
    result = "I'm composite unit!\nPosition: X = " + std::to_string(position.x) + "; Y = " + std::to_string(position.y) + "\nIncludes:\n";
    for(auto const& instance : units)
    {
        result += instance->getUnitInf();
    }
    return result;
}

void CompositeUnit::reallocation(size_t new_x, size_t new_y)
{
    Unit::reallocation(new_x, new_y);
    for(const auto &curr : units)
    {
        curr->reallocation(new_x, new_y);
    }
}

CompositeUnit *CompositeUnit::isComposite()
{
    return this;
}

Unit *CompositeUnit::clone() const
{
    return new CompositeUnit(*this);
}

void CompositeUnit::addUnit(std::shared_ptr<Unit> unit)
{
    units.push_back(unit);
}

size_t CompositeUnit::getUnitQuantity() const
{
    return units.size();
}

void CompositeUnit::initCurrPar()
{
    health = getHealth();
    armor = getArmor();
    meleeAttackStrength = getMeleeAttackStrength();
    movementRange = COMPOSITE_UNIT_MOVEMENT_RANGE;
    actionTokens = COMPOSITE_UNIT_ACTION_TOKENS;
}

std::map<eUnitsType, size_t> CompositeUnit::getComposition()
{
    std::map<eUnitsType, size_t> result;
    for (const auto& curr : units)
    {
        if(result.find(curr->getType()) != result.end())
        {
            result[curr->getType()]++;
        }
        else
        {
            result.insert(std::pair<eUnitsType, size_t>(curr->getType(), 1));
        }
    }

    return result;
}

eUnitsType CompositeUnit::getType()
{
    return eUnitsType::COMPOSITE_UNIT;
}

/**
 * If members of composite unit have enough armor - it's okey,
 * they take it and go next without loosing a health
 * (damage is distributed to all).
 *
 * If it's not: count death factor - if it's < then affordable
 * health -> take damage for all armor and health (make it == 1).
 * Other possible cure in army ;)
 *
 * If > -> unit die.
 * @param damageSize
 */
void CompositeUnit::takeDamage(size_t damageSize)
{
    if(getArmor() >= damageSize)
    {
        size_t i = 0;
        while(damageSize > 0)
        {
            if(units[i]->getArmor() > 0)
            {
                units[i]->takeDamage(1);
                damageSize--;
            }
            i++;
            if(i + 1 == units.size())
                i = 0;
        }
        return;
    }
    else
    {
        damageSize -= getArmor();
        if(damageSize > static_cast<size_t >(COMPOSITE_UNIT_DEATH_FACTOR * damageSize))
        {
            notifyObserversAboutDeath();
        }
        else
        {
            size_t i = 0;
            while(damageSize > 0)
            {
                if(units[i]->getHealth() > 1)
                {
                    units[i]->takeDamage(1);
                    damageSize--;
                }
                else
                {
                    if(i + 1 == units.size())
                        break;
                }
                i++;
                if(i + 1 == units.size())
                    i = 0;
            }
        }
    }
}

void CompositeUnit::setMeleeAttackBoost(size_t boost)
{
    size_t i = 0;
    for( ; boost > 0; i++)
    {
        units[i]->setMeleeAttackBoost(1);
        boost--;
        if(i + 1 == boost)
            i = 0;
    }
}

void CompositeUnit::setArmorBoost(size_t boost)
{
    size_t i = 0;
    for( ; boost > 0; i++)
    {
        units[i]->setArmorBoost(1);
        boost--;
        if(i + 1 == boost)
            i = 0;
    }
}
