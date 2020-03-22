#ifndef OOP_HELLBASEBUILDER_H
#define OOP_HELLBASEBUILDER_H

#include "BaseBuilder.h"
#include "HellBase.h"

class HellBaseBuilder : public BaseBuilder
{
protected:
    std::shared_ptr<HellBase> base;
public:
    HellBaseBuilder() : BaseBuilder() { }
    ~HellBaseBuilder() override = default;

    void createNewBase() override;
    std::shared_ptr<GameBase> getBase() override;
    void buildUnitCount() override;
    void buildFabric() override;
};

#endif //OOP_HELLBASEBUILDER_H
