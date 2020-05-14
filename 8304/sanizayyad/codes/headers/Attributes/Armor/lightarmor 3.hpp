#ifndef lightarmor_hpp
#define lightarmor_hpp

#include "armor.hpp"

#include <stdio.h>


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
    virtual std::string getAmorType() const override;
    

};

#endif /* lightarmor_hpp */
