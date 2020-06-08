#ifndef BASE_H
#define BASE_H

#include "game_elements/buildings/building.h"
#include "game_elements/team.h"

#include <SFML/System/Vector2.hpp>


class WorkerUnitFactory;

class Base: public Building
{
public:
    inline static float initial_max_health = 20;

private:
    inline static const std::string id = "building_base";
    Team team;
    WorkerUnitFactory *factory;
    sf::Vector2i pos;

    Building::Rot rot;

    float maxHealth;
    float health;

    bool toDelete = 0;

    void setPosition(int x, int y) override;

public:
    ~Base();
    Base(Team team, const sf::Vector2i& pos, Rot rot = Rot::Down);
    Entity * copy() const override;
    virtual void update(float time) override;

    void damage(float dmg) override;
    void setHealth(float hp) override;

    float getHealth() const override;
    float getMaxHealth() const override;
    Building::Rot getRotation() const override;   // face of the building
    const sf::Vector2i& getPosition() const override;

    class Unit* createUnit(Unit::Type) override;

    bool delete_p() const override;

    Team getTeam() const override;
    std::string getInfo() const override;
    Building::Type getBuildingType() const override {return Building::Base; }
    const std::string& getID() const override;
};

#endif // BASE_H
