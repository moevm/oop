#ifndef HELTHCARD_H
#define HELTHCARD_H

#include "neutralobkect.h"

class PositiveCard : public Neutral
{
private:
    std::string name_plus;
public:
    PositiveCard(){}
    std::string name() override{
        name_plus = "positive_card";

    }
    void operator +(Unit* unit){
        unit->health += 10;
        unit->armor += 10;
        unit->attack +=10;
    }

};

#endif // HELTHCARD_H
