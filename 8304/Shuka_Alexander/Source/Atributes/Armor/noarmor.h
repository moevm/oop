#ifndef NOARMOR_H
#define NOARMOR_H

#include "armor.h"


class NoArmor : public Armor
{
public:
    explicit NoArmor();
    virtual ~NoArmor() = default;

    NoArmor(const NoArmor& armor);
    NoArmor(NoArmor&& armor) = delete;
    NoArmor& operator=(const NoArmor& armor);
    NoArmor& operator=(NoArmor&& armor) = delete;

    virtual std::unique_ptr<Armor> clone() override;

    virtual double getResistance() const override;
};

#endif // NOARMOR_H
