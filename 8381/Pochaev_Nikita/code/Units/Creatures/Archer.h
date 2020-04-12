#ifndef OOP_ARCHER_H
#define OOP_ARCHER_H

#include "../Unit.h"
#include "../IShooter.h"

class Archer : public Unit, public IShooter
{
public:
    Archer();
    Archer* clone() const override;
    explicit Archer(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void shot() override;
    void canopyShooting() override;

    ~Archer() override;
};

#endif //OOP_ARCHER_H
