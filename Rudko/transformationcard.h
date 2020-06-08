#ifndef TRANSFORMATIONCARD_H
#define TRANSFORMATIONCARD_H

#include "neutralobkect.h"

class TransformationCard : public Neutral, public Unit
{
private:
    std::string name_transform;
public:
    TransformationCard(){
        this->type = "neutral";
    }
    std::string name() override{
        name_transform = "transformation_card";

    }

    void operator*(Unit* unit){
        unit->attack += 20;
        unit->armor -= 10;
    }

};

#endif // TRANSFORMATIONCARD_H
