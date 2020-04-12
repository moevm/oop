#ifndef OOP_KNIGHT_H
#define OOP_KNIGHT_H

#include "../Unit.h"
#include "../ICavalry.h"

class Knight : public Unit, public ICavalry
{
public:
    Knight();
    Knight* clone() const override;

    explicit Knight(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void postMortem() override;
    void armament() override;

    ~Knight() override;
};

#endif //OOP_KNIGHT_H
