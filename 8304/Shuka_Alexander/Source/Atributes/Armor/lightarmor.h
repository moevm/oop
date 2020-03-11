#ifndef LIGHTARMOR_H
#define LIGHTARMOR_H

#include "armor.h"


class LightArmor : public Armor
{
public:
    explicit LightArmor();
    virtual ~LightArmor() = default;

    LightArmor(const LightArmor& armor);
    LightArmor(LightArmor&& armor) = delete;
    LightArmor& operator=(const LightArmor& armor);
    LightArmor& operator=(LightArmor&& armor) = delete;

    virtual std::unique_ptr<Armor> clone() override;

    virtual double getResistance() const override;
};

#endif // LIGHTARMOR_H
