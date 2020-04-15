#ifndef OOP_HECK_H
#define OOP_HECK_H

#include "../Unit.h"
#include "../ICannonFodder.h"

class Heck : public Unit, public ICannonFodder
{
public:
    Heck();
    Heck* clone() const override;

    explicit Heck(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void train() override;
    bool cowardice() override;

    ~Heck() override;
};

#endif //OOP_HECK_H
