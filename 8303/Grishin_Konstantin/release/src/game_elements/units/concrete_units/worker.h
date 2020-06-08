#ifndef WORKER_H
#define WORKER_H

#include "game_elements/units/unit.h"
#include "game_elements/units/unit_stats.h"



class Worker : public Unit
{
public:
    inline static const std::string id = "unit_worker";

private:
    friend class WorkerUnitFactory;
    enum class State{
        Stands,
        Works,
        Moves,
        Damaged
    };

    const Team team;
    sf::Vector2i pos;

    void setPosition(int x, int y) override;

    float timer = 0;
    sf::Vector2f oldPosition;
    State state;

    const UnitStats &stats;
    float extraSteps;
    float health;
    float steps;

    int target_x = -1;
    int target_y = -1;

    void constructAction(UnitAction& action) const override;

    void setMoveState();
    void setWorkState();

    bool toDelete = 0;
    bool moving = 0;

    Worker(Team team, const sf::Vector2i& pos, const UnitStats &stats);

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

    Team getTeam() const override;
    const sf::Vector2i& getPosition() const override;

    void setActionState() override;
    void setTarget(int x, int y);
    sf::Vector2i getTarget() const;
    void move(int x, int y) override;
    bool isMovable() const override;

    Unit::Type getUnitType() const override;

    bool delete_p() const override;

    std::string getInfo() const override;
    const std::string& getID() const override;
};

#endif // WORKER_H
