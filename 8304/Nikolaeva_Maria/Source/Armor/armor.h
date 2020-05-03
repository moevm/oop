#ifndef ARMOR_H
#define ARMOR_H

constexpr double NO_ARMOR = 1;
constexpr double LIGHT_ARMOR = 1;
constexpr double HEAVY_ARMOR = 1;


class Armor
{
public:
    virtual ~Armor() = default;

    virtual double getResistance() const = 0;

    virtual Armor* clone() = 0;

protected:
    double resistance;
};

#endif // ARMOR_H
