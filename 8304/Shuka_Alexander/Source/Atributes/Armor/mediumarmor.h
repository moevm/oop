#ifndef MEDIUMARMOR_H
#define MEDIUMARMOR_H

#include "armor.h"


class MediumArmor : public Armor
{
public:
    explicit MediumArmor();
    virtual ~MediumArmor() = default;

    MediumArmor(const MediumArmor& armor);
    MediumArmor(MediumArmor&& armor) = delete;
    MediumArmor& operator=(const MediumArmor& armor);
    MediumArmor& operator=(MediumArmor&& armor) = delete;

    virtual std::unique_ptr<Armor> clone() override;

    virtual double getResistance() const override;
};

#endif // MEDIUMARMOR_H
