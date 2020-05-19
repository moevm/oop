#ifndef heavyarmor_hpp
#define heavyarmor_hpp

#include "armor.hpp"

#include <stdio.h>


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
    virtual std::string getAmorType() const override;
    

};

#endif /* heavyarmor_hpp */
