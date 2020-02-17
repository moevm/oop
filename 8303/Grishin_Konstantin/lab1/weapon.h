#ifndef WEAPON_H
#define WEAPON_H


struct Shell{
    enum Type{
        straight,
        siege,
        pure
    };

    Type type;
    int iDamage;
};


class Weapon
{
protected:
    int iMaxDurability;

    int iDurability;
    float fDamageFactor;

    Shell::Type type;

public:
    virtual ~Weapon(){}

    explicit Weapon(Shell::Type type, int durability, float dmg_fact);
    virtual Shell attack() = 0;
};


class Club: public Weapon
{
private:
    int iDamage;
public:
    Club(Shell::Type type, int durability, int damage, float dmg_fact);
    Shell attack() override;
};

#endif // WEAPON_H
