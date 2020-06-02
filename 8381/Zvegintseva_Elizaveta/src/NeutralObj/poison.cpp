#include "poison.h"

DrinkPoison::DrinkPoison(Poison* pos):poison(pos)
{

}

void DrinkPoison::operator +=(Unit &unit)
{
    poison->use(unit);
}

DrinkPoison::~DrinkPoison()
{
    delete poison;
}

void Belladonna::use(Unit &unit)
{
    unit.getAttributes()->setHealth(unit.getAttributes()->getHealth()-19);
}

NeutralType Belladonna::type()
{
    return BELLADONNA;
}

void Cyanide::use(Unit &unit)
{
    unit.getAttributes()->setHealth(unit.getAttributes()->getHealth()-37);
}

NeutralType Cyanide::type()
{
    return CYANIDE;
}

string DrinkPoison::getType()const{
    return "neutral";
}

NeutralType DrinkPoison::getTypeEnum()
{
    return poison->type();
}


string DrinkPoison::characteristic()
{
    return "DrinkPoison";
}
