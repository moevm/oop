#ifndef OOP_HUMANBASEBUILDER_H
#define OOP_HUMANBASEBUILDER_H

#include "BaseBuilder.h"
#include "HumanBase.h"

class HumanBaseBuilder : public BaseBuilder
{
protected:
    std::shared_ptr<HumanBase> base;
public:
    HumanBaseBuilder() : BaseBuilder() { }
    ~HumanBaseBuilder() override = default;

    void createNewBase() override;
    std::shared_ptr<GameBase> getBase() override;
    void buildUnitCount() override;
    void buildFabric() override;
};

#endif //OOP_HUMANBASEBUILDER_H
