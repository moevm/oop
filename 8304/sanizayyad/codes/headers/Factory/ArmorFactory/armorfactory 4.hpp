#ifndef armorfactory_hpp
#define armorfactory_hpp

#include "armor.hpp"
#include "noarmor.hpp"
#include "lightarmor.hpp"
#include "mediumarmor.hpp"
#include "heavyarmor.hpp"

#include <memory>
#include <stdio.h>

class ArmorFactory
{
public:
    explicit ArmorFactory() = default;
    virtual ~ArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() = 0;
};

#endif /* armorfactory_hpp */
