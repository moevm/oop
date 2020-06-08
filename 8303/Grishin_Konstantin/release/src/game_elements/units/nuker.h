#ifndef NUKER_H
#define NUKER_H

#include <game_elements/units/unit.h>

class Nuker : public Unit
{
private:
    const Team team;
    sf::Vector2i pos;

    virtual void setPosition(int x, int y) override;

protected:
    virtual void setMoveState() = 0;
    virtual void setAttackState() = 0;

    bool toDelete = 0;
    bool moving = 0;

    Nuker(Team team, const sf::Vector2i& pos);

public:
    Team getTeam() const override;
    const sf::Vector2i& getPosition() const override;

    void setActionState() override;
    void move(int x, int y) override;
    bool isMovable() const override;

    Unit::Type getUnitType() const override;

    bool delete_p() const override;
};

#endif // NUKER_H
