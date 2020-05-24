
#ifndef noarmor_hpp
#define noarmor_hpp

#include "armor.hpp"

#include <stdio.h>

 class NoArmor : public Armor
 {
 public:
     explicit NoArmor();
     virtual ~NoArmor() = default;

     NoArmor(const NoArmor& armor);
     NoArmor(NoArmor&& armor) = delete;
     NoArmor& operator=(const NoArmor& armor);
     NoArmor& operator=(NoArmor&& armor) = delete;

     virtual double getResistance() const override;
     virtual std::string getAmorType() const override;
     
     virtual std::unique_ptr<Armor> clone() override;

 };

#endif /* noarmor_hpp */
