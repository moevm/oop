#ifndef ATRONS_H
#define ATRONS_H

#include "game_elements/units/range.h"
#include "game_elements/units/unit_stats.h"

class Atrons : public Range
{
public:
    inline static const std::string id = "unit_atrons";
    
private:
    enum class State{
        Stands,
        Attacks,
        Moves,
        Damaged
    };


    friend class MagicUnitFactory;
    float timer = 0;
    sf::Vector2f oldPosition;
    State state;

    const UnitStats &stats;
    float extraDamage;
    float health;
    float steps;
    
    Atrons(Team team, const sf::Vector2i& pos, const UnitStats &stats);
    void setMoveState() override;
    void setAttackState() override;

    void constructAction(UnitAction &action) const override;
    
public:
    Entity * copy() const override;
    void update(float time) override;
    sf::Vector2f getMovingOffset() const override;

    void setHealth(float hp) override;
    void setSteps(float steps) override;
    void setExtra(float extra) override;

    void damage(float dmg, const std::string& id) override;
    virtual void heal(float hp) override;
    virtual void increase(float val) override;
    virtual void resetSteps() override;

    float getHealth() const override;
    float getMaxHealth() const override;

    float getSteps() const override;
    float getMaxSteps() const override;

    float getExtra() const override;

    std::string getInfo() const override;
    const std::string& getID() const override;
};

#endif // ATRONS_H
