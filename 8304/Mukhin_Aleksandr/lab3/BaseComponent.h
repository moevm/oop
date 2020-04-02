#ifndef LAB2_BASECOMPONENT_H
#define LAB2_BASECOMPONENT_H


#include <memory>
#include "BaseMediator.h"
class BaseMediator;
class BaseComponent {
protected:
    BaseMediator* mediator = nullptr;

public:
    BaseComponent() = default;
    BaseComponent(BaseMediator* med) : mediator(med) {}
    void set_mediator(BaseMediator*);
};


#endif
