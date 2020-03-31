#ifndef OOP_BASEMASTER_H
#define OOP_BASEMASTER_H

#include "BaseBuilder.h"

class BaseMaster
{
private:
    BaseBuilder* baseBuilder;
public:
    BaseMaster() : baseBuilder(nullptr) { }
    ~BaseMaster() = default;

    void setBaseBuilder(BaseBuilder *baseBuilder_);
    std::shared_ptr<GameBase> getBase();
    void constructBase();
};

#endif //OOP_BASEMASTER_H
