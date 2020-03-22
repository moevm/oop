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

    [[nodiscard]] bool meleeAttack(size_t x, size_t y) const override;
    void describeYourself() override;
    std::string getType() override;

    void postMortem() override;
    void armament() override;

    ~Knight() override;
};

#endif //OOP_KNIGHT_H
