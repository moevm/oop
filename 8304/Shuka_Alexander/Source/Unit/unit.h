#ifndef UNIT_H
#define UNIT_H

#include <memory>

#include "Field/point2d.h"

#include "Atributes/Armor/armor.h"
#include "Atributes/Weapon/weapon.h"

#include "imovable.h"
#include "ifarming.h"


class Unit : public IMovable, public IFarming
{
public:
    explicit Unit(const Point2D& point);
    virtual ~Unit() = default;

    Unit(const Unit& unit);

    int getHealthPoints() const;
    const Point2D& getPosition() const;
    const std::unique_ptr<Armor>& getArmor() const;
    const std::unique_ptr<Weapon>& getWeapon() const;
    
    void setWeapon(std::unique_ptr<Weapon> weapon);
    void setArmor(std::unique_ptr<Armor> armor);

    virtual bool isFly() const = 0;

    virtual std::shared_ptr<Unit> clone() = 0;
    
protected:    
    void doCopy(const Unit& unit);
    
protected:
    Point2D position;
    int healthPoints;
    std::unique_ptr<Armor> armor;
    std::unique_ptr<Weapon> weapon;
    // std::shared_ptr<Mediator> mediator;
};

#endif // UNIT_H
