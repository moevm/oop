#pragma once

class IUnit;


class NeutralObject {
public:
    virtual bool operator>>(IUnit& unit) = 0;
};


class HealOffice : public NeutralObject
{
public:
    bool operator>>(IUnit& unit) override;
};


class DamageOffice : public NeutralObject
{
public:
    bool operator>>(IUnit& unit) override;
};


class ArmorOffice : public NeutralObject
{
public:
    bool operator>>(IUnit& unit) override;
};


class MovementOffice : public NeutralObject
{
public:
    bool operator>>(IUnit& unit) override;
};
