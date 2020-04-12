#ifndef OOP_ENERGYPOTION_H
#define OOP_ENERGYPOTION_H

#include "NeutralObject.h"

class EnergyPotion : public NeutralObject
{
public:
    ~EnergyPotion() override = default;
    void operator+= (const std::shared_ptr<Unit> &unit) override;
    std::string getNameOfNeutralObject() override;
};

#endif //OOP_ENERGYPOTION_H
