#ifndef OOP_SUCCUBUS_H
#define OOP_SUCCUBUS_H

#include "../Unit.h"
#include "../IShooter.h"

class Succubus : public Unit, public IShooter
{
public:
    Succubus();
    Succubus* clone() const override;

    explicit Succubus(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void shot() override;
    void canopyShooting() override;

    ~Succubus() override;
};

#endif //OOP_SUCCUBUS_H
