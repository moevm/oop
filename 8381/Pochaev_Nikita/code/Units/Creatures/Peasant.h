#ifndef OOP_PEASANT_H
#define OOP_PEASANT_H

#include <utility>

#include "../Unit.h"
#include "../ICannonFodder.h"

class Peasant : public Unit, public ICannonFodder
{
public:
    Peasant();
    Peasant* clone() const override;

    explicit Peasant(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void train() override;
    bool cowardice() override;

    ~Peasant() override;
};

#endif //OOP_PEASANT_H
