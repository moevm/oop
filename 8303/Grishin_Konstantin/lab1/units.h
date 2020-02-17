#ifndef UNITS_H
#define UNITS_H

#include <string>

#include "point.h"

namespace sf {
    class RenderTarget;
}


class Weapon;


class Entity{
public:
    enum Attack{
        Absent,
        Melee,
        Range
    };
    enum Unit{
        Building,
        Peace,
        Siege,
        Infantry
    };

protected:
    Attack attack_type;
    Unit unit_type;

    bool selected = 0;
    int iMaxSteps = 0;
    int iRemainedSteps = 0;


    Point position = Point(0,0);

    int iHealth;
    bool bAlive; // alive_p

public:
    explicit Entity(const Point &pos, int health);

    virtual void draw(sf::RenderTarget* target, int cell_size) = 0;
    virtual void damage(int dmg) = 0;       // Show getting damaged animation and decrease hp
    virtual void move(const Point &offset) = 0;    // Show move animation and change position
    virtual void fire(Entity *enemy) = 0;    // Show attack animation and damage enemy
    virtual void nextStep() = 0;
    virtual ~Entity(){}

    Point pos() const;
    Attack attackType() const;
    Unit unitType() const;
    int health() const;

    bool isAlive() const;

    void select();
    void deselect();
    bool selected_p() const;

    int remainigSteps() const;
};


// Melee unit, with infantry abilities
class Melee: public Entity
{
private:
    Weapon *weapon;

public:
    Melee(Point pos, int health, int damage, int steps);
    void draw(sf::RenderTarget *target, int cell_size) override;

    void damage(int dmg) override;
    void move(const Point &offset) override;
    void fire(Entity *enemy) override;
    void nextStep() override;
};


// Range unit, with infantry abilities
class Range: public Entity{
private:
    Weapon *weapon;

    int iAttackRange;
    int iBlindZone;

public:
    Range(Point pos, int health, int steps, int inner_range, int outer_range);
    void draw(sf::RenderTarget *target, int cell_size) override;

    void damage(int dmg) override;
    void move(const Point &offset) override;
    void fire(Entity *enemy) override;
    void nextStep() override;

    int attackRange() const;
    int blindZone() const;
};


// Absent unit, with peacfully abilities
class Absent: public Entity{
    // create or repair buildings

public:
    Absent(Point pos, int health, int steps);
    void draw(sf::RenderTarget *target, int cell_size) override;

    void damage(int dmg) override;
    void move(const Point &offset) override;
    void fire(Entity *enemy) override;
    void nextStep() override;
};







#endif // UNITS_H
