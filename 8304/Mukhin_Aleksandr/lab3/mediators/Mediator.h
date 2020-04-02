#ifndef LAB2_MEDIATOR_H
#define LAB2_MEDIATOR_H


#include <Unit.h>
#include <NeutralObject.h>
#include "BaseMediator.h"

class Mediator : public BaseMediator {
private:
    std::shared_ptr<Unit> unit = nullptr;
    std::shared_ptr<NeutralObject> neutral_object = nullptr;

public:
    Mediator(std::shared_ptr<Unit>& c1, std::shared_ptr<NeutralObject>& c2) : unit(c1), neutral_object(c2) {
        unit->set_mediator(this);
        neutral_object->set_mediator(this);
    }

    void make_action() const override;
};


#endif
