#include "attackmediator.h"

AttackMediator::AttackMediator(Field *field)
    :field(field) {}

void AttackMediator::addUnit(IUnit *unit)
{
    unit->setAttackMediator(this);
    units.push_back(unit);
}

void AttackMediator::removeUnit(IUnit *unit)
{
    for (unsigned i=0; i<units.size(); i++)
        if (units[i] == unit)
            units.erase(units.begin() + i);
}

bool AttackMediator::attack(IUnit *attacker, int deltaX, int deltaY)
{
    unsigned attX = 0;
    unsigned attY = 0;
    bool found = false;
    for (FieldIterator iter(field); iter.isActive(); ++iter)
    {
        if (iter.operator->() == attacker)
        {
            found = true;
            attX = iter.getCurWidth();
            attY = iter.getCurHeight();
            break;
        }
    }
    unsigned defX = static_cast<unsigned>(static_cast<int>(attX) + deltaX);
    unsigned defY = static_cast<unsigned>(static_cast<int>(attY) + deltaY);
    FieldItem *defender = field->getItem(defX, defY);
    for (auto i : units)
    {
        if (i == defender)
        {
            if (i->getBaseNumber() == attacker->getBaseNumber())
                throw std::invalid_argument("units from one base");
            if (!i->receiveAttack(attacker))
            {
                field->deleteItem(defX, defY);
                return false;
            }
            return true;
        }
    }
    throw std::invalid_argument("defender is not unit");
}

std::vector<IUnit *> AttackMediator::getUnits() const
{
    return units;
}
