#include "adapter.h"
#include "field.h"

using namespace std;

ostream& operator<< (ostream& out,  Unit& unit)
{
    return out << unit.getClassName() << ". Health = " << unit.getHealth() << ", Armor = " << unit.getArmor() <<
                  ", Damage = " << unit.getDamage() << ". Base type = "<< unit.getArmy() <<
                  ". On position = (" << unit.getX() << "," << unit.getY() << ")";
}

string Adapter::adaptUnitCreate(Unit* unit)
{
    ostringstream outstr("");
    outstr << "Log: Unit was created: " << *unit << "\n";
    return outstr.str();
}


string Adapter::adaptUnitMove(Unit* unit , int x, int y)
{
    ostringstream outstr("");
    outstr << "Log: Unit was moved: " << *unit << "moved to position = (" << x << ", " << y <<")\n";
    return outstr.str();
}

string Adapter::adaptUnitUnderAttack(Unit* unit)
{
    ostringstream outstr("");
    outstr << "Log: Unit was attacked: " << *unit << "\n";
    return outstr.str();
}

string Adapter::adaptUnitRemove(Unit* unit)
{
    ostringstream outstr("");
    outstr << "Log: Unit was removed: " << *unit << "\n";
    return outstr.str();
}

string Adapter::adaptUnitPrint(Unit* unit)
{
    ostringstream outstr("");
    outstr << "Unit: " << *unit << "\n";
    return outstr.str();
}

ostream& operator<< (ostream& out,  Base& base)
{
    return out << base.getBaseName() << "base: Health " << base.getHealth() << ". Current number of units and max number of units - "
               << base.getCurrUnits() << "/" << base.getMaxUnits();
}

string Adapter::adaptBaseCreate(Base* base)
{
    ostringstream outstr("");
    outstr << "Log: Base was created: " << *base << "\n";
    return outstr.str();
}

string Adapter::adaptBaseUnderAttack(Base* base)
{
    ostringstream outstr("");
    outstr << "Log: Base was attacked: " << *base << "\n";
    return outstr.str();
}

string Adapter::adaptGameOver(Base* base)
{
    ostringstream outstr("");
    outstr << "Log: Game over:" << base->getBaseName() <<  " base lose\n";
    return outstr.str();
}




