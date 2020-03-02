#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Unit;

class Weapon
{
protected:
    enum Type{
        physical,
        siege,
        pure
    };

private:
    const std::string name;
    const Type wType;
    const int iDamage;
    const int iMaxRange;

public:
    virtual ~Weapon(){}
    Weapon(Type wType, int iDamage, int iMaxRange, const std::string& name);

    virtual float fire(const Unit& enemy) const = 0;

    int damage() const;
    int maxRange() const;
    const std::string& getName() const;
};


class MeleeWeapon: public Weapon
{
    bool bDefenseMode;
public:
    MeleeWeapon(Type type, int iDamage, const std::string& name);
    void changeMode();
    bool mode();
};


class Club: public MeleeWeapon
{
public:
    Club();
    float fire(const Unit& enemy) const;
};


class RangeWeapon: public Weapon
{
private:
    const int iBlindZone;

public:
    RangeWeapon(Type type, int iDamage, int iMaxRange, int iBlindZone, const std::string& name);
};


class Bow: public RangeWeapon
{
public:
    Bow();
    float fire(const Unit& enemy) const;
};


class NukerWeapon: public Weapon
{
private:
    const int iBlindZone;

public:
    NukerWeapon(Type type, int iDamage, int iMaxRange, int iBlindZone, const std::string& name);
};


class Scythe : public NukerWeapon
{
public:
    Scythe();
    float fire(const Unit& enemy) const;
};
















#endif // WEAPON_H
