#pragma once

#include <cstdint>


class Strength
{
public:
    Strength();
    Strength(uint16_t strength, uint8_t radius);

    void setStrength(uint16_t strength);
    void setRadius(uint8_t radius);
    uint16_t getStrength();
    uint8_t getRadius();

private:
    uint16_t strength;
    uint8_t radius;
};


class Armor
{
public:
    Armor();
    Armor(uint16_t armor);

    void setArmor(uint16_t armor);
    uint16_t getArmor();

private:
    uint16_t armor;
};


class Health
{
public:
    Health();
    Health(uint16_t maxHealth, uint16_t health);

    void setMaxHealth(uint16_t maxHealth);
    void setHealth(uint16_t health);
    uint16_t getMaxHealth();
    uint16_t getHealth();

private:
    uint16_t maxHealth;
    uint16_t health;
};


class MovePoints {
public:
    MovePoints();
    MovePoints(uint8_t maxMovePoints, uint8_t movePoints);

    void setMaxMovePoints(uint8_t maxMovePoints);
    void setMovePoints(uint8_t movePoints);
    uint8_t getMaxMovePoints();
    uint8_t getMovePoints();

private:
    uint8_t maxMovePoints;
    uint8_t movePoints;
};
