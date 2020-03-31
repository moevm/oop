#ifndef OOP_BASEBUILDER_H
#define OOP_BASEBUILDER_H

#include "GameBase.h"

// Abstract Builder
class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;
    virtual std::shared_ptr<GameBase> getBase() = 0;
    virtual void createNewBase() = 0;
    virtual void buildUnitCount() = 0;

    virtual void buildFabric() = 0;
};

#endif //OOP_BASEBUILDER_H
