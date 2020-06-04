#ifndef DEATHCARD_H
#define DEATHCARD_H

#include "neutralobkect.h"
#include "gfield.h"

class DeathCard : public Neutral
{
private:
    std::string name_death;
    GField* field;
public:
    DeathCard(GField* field){}
    std::string name() override{
        name_death = "death_card";

    }
    void operator /(Unit* unit){
        this->field = field;
        field->deleteUnite(unit);
    }

};

#endif // DEATHCARD_H
