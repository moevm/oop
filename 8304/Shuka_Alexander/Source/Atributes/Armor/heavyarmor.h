#ifndef HEAVYARMOR_H
#define HEAVYARMOR_H

#include "armor.h"


class HeavyArmor : public Armor
{
public:
    explicit HeavyArmor();
    virtual ~HeavyArmor() = default;

    HeavyArmor(const HeavyArmor& armor);
    HeavyArmor(HeavyArmor&& armor) = delete;
    HeavyArmor& operator=(const HeavyArmor& armor);
    HeavyArmor& operator=(HeavyArmor&& armor) = delete;

    virtual std::unique_ptr<Armor> clone() override;

    virtual double getResistance() const override;
};

#endif // HEAVYARMOR_H
