#ifndef noarmorfactory_hpp
#define noarmorfactory_hpp

#include "armorfactory.hpp"

#include <stdio.h>

class NoArmorFactory : public ArmorFactory
{
public:
    explicit NoArmorFactory() = default;
    virtual ~NoArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};

#endif /* noarmorfactory_hpp */
