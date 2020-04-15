#ifndef OOP_LEGENDARYWEAPON_H
#define OOP_LEGENDARYWEAPON_H

#include "NeutralObject.h"

class LegendaryWeapon : public NeutralObject
{
public:
    ~LegendaryWeapon() override = default;
    void operator+= (const std::shared_ptr<Unit> &unit) override;
    std::string getNameOfNeutralObject() override;
};

#endif //OOP_LEGENDARYWEAPON_H
