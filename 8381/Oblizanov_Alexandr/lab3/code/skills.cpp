#include "skills.h"

Skills::Skills()
{
    setMove(0);
    setBonus(0);
    setPower(0);
    setSpread(0);
}

void Skills::setAll(int move, int power, int spread, int bonus)
{
    setMove(move);
    setBonus(bonus);
    setPower(power);
    setSpread(spread);
}

int Skills::getMove() const
{
    return move;
}

void Skills::setMove(int value)
{
    move = value;
}

void Skills::reduceMove(int value)
{
    value -= bonus;
    if (value > 0)
    {
        bonus = 0;
        move -= value;
        if (move < 0)
            move = 0;
    }
}


int Skills::getPower() const
{
    return power;
}

void Skills::setPower(int value)
{
    power = value;
}

void Skills::reducePower(int value)
{
    value -= bonus;
    if (value > 0)
    {
        bonus = 0;
        power -= value;
        if (power < 0)
            power = 0;
    }
}

int Skills::getSpread() const
{
    return spread;
}

void Skills::setSpread(int value)
{
    spread = value;
}

void Skills::reduceSpread(int value)
{
    value -= bonus;
    if (value > 0)
    {
        bonus = 0;
        spread -= value;
        if (spread < 0)
            spread = 0;
    }
}

int Skills::getBonus() const
{
    return bonus;
}

void Skills::setBonus(int value)
{
    bonus = value;
}
