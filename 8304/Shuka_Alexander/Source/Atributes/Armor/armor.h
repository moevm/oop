#ifndef ARMOR_H
#define ARMOR_H

#include <memory>


constexpr double NO_ARMOR = 0.0;
constexpr double LIGHT_ARMOR = 0.25;
constexpr double MEDIUM_ARMOR = 0.5;
constexpr double HEAVY_ARMOR = 0.75;


class Armor
{
public:
    virtual ~Armor() = default;

    virtual double getResistance() const = 0;

    virtual std::shared_ptr<Armor> clone() const = 0;

protected:
    void doCopy(const Armor& armor);

protected:
    double resistance;
};

#endif // ARMOR_H
