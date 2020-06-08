#ifndef BATTLEFORHONOUR_NEUTRALOBJECT_H
#define BATTLEFORHONOUR_NEUTRALOBJECT_H


#include "../GameObject.h"
#include "NeutralObjectStrategy.h"
#include "../Unit.h"

class Unit;

class NeutralObject: public GameObject {

protected:
    NeutralObjectStrategy *strategy{};

public:
    NeutralObject():
        GameObject(ObjectType::NEUTRAL_OBJECT){}

    void setStrategy(NeutralObjectStrategy *strategy) {
        this->strategy = strategy;
    }
    virtual void toEffect(Unit &unit)=0;

    virtual ~NeutralObject(){

        delete strategy;

    }

};


#endif //BATTLEFORHONOUR_NEUTRALOBJECT_H
