#include "base.h"

Base::Base(Field* field)
    : field(field) ,name("BAS"), health(20000), itemLimit(15), itemCounter(0)
{
    supportFactory = new SupportFactory();
    rangeFactory = new RangeFactory();
    meleeFactory = new MeleeFactory();
}
Base::Base(Field* field, unsigned itemLimit)
    : field(field), name("BAS"), health(20000),itemLimit(itemLimit), itemCounter(0)
{
    supportFactory = new SupportFactory();
    rangeFactory = new RangeFactory();
    meleeFactory = new MeleeFactory();
}

unsigned Base::getHealth() const
{
    return health;
}

std::string Base::shortName()
{
    return  "ⒷⒶⓈⒺ";
}

FieldItem* Base::addOrk(unsigned x, unsigned y)
{
    if(itemCounter<itemLimit){
        auto unit = meleeFactory->createDire();
        if(field->addItem(x,y,unit)){
            itemCounter++;
            std::cout << unit->about() << "was born\n";
            return unit;
        }
    }
    throw std::invalid_argument("no such item on field");
}

FieldItem* Base::addKnight(unsigned x, unsigned y)
{
    if(itemCounter<itemLimit){
        auto unit = meleeFactory->createRadiant();
        if(field->addItem(x,y, unit)){
            itemCounter++;
            std::cout << unit->about() << "was born\n";
            return unit;
        }
    }
    throw std::invalid_argument("no such item on field");
}

FieldItem* Base::addDryad(unsigned x, unsigned y)
{
    if(itemCounter<itemLimit){
        auto unit = supportFactory->createRadiant();
        if(field->addItem(x,y,unit)){
            itemCounter++;
            std::cout << unit->about() << "was born\n";
            return unit;
        }
    }
    throw std::invalid_argument("no such item on field");
}

FieldItem* Base::addWitch(unsigned x, unsigned y)
{
    if(itemCounter<itemLimit){
        auto unit = supportFactory->createDire();
        if(field->addItem(x,y,unit)){
            itemCounter++;
            std::cout << unit->about() << "was born\n";
            return unit;
        }
    }
    throw std::invalid_argument("no such item on field");
}

FieldItem* Base::addDragon(unsigned x, unsigned y)
{
    if(itemCounter<itemLimit){
        auto unit = rangeFactory->createRadiant();
        if(field->addItem(x,y, unit)){
            itemCounter++;
            std::cout << unit->about() << "was born\n";
            return unit;
        }
    }
    throw std::invalid_argument("no such item on field");
}

FieldItem* Base::addChimera(unsigned x, unsigned y)
{
    if(itemCounter<itemLimit){
        auto unit = rangeFactory->createDire();
        if(field->addItem(x,y, unit)){
            itemCounter++;
            std::cout << unit->about() << "was born\n";
            return unit;
        }
    }
    throw std::invalid_argument("no such item on field");
}

FieldItem* Base::deleteUnit(FieldItem *obj)
{
    itemCounter--;
    std::string tmp = obj->shortName();
    field->deleteItem(obj);
    std::cout << "Rest In peace, " << tmp << "\n";

}





