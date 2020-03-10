#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

enum struct HpTypes : unsigned
{
    ARCHER    = 1000, WIZARD   = 750,
    SWORDSMAN = 1500, SPEARMAN = 750,
    CENTAUR   =  750, PANZER   = 2000
};

enum struct RngTypes : unsigned
{
    ARCHER    = 3, WIZARD   = 2,
    SWORDSMAN = 1, SPEARMAN = 1,
    CENTAUR   = 1, PANZER   = 1
};

enum struct DmgTypes : unsigned
{
    ARCHER    = 100, WIZARD   = 250,
    SWORDSMAN = 150, SPEARMAN =  75,
    CENTAUR   =  50, PANZER   = 100
};

enum struct ArmTypes : unsigned
{
    ARCHER    = 100, WIZARD   =   0,
    SWORDSMAN = 250, SPEARMAN = 100,
    CENTAUR   =   0, PANZER   = 500
};

enum struct ManaTypes : unsigned
{
    ARCHER    = 0, WIZARD   = 500,
    SWORDSMAN = 0, SPEARMAN =   0,
    CENTAUR   = 0, PANZER   =   0
};

class Attributes
{
public:
    unsigned health;
    unsigned range ;
    unsigned damage;
    unsigned armor ;
    unsigned mana  ;
    Attributes(HpTypes, RngTypes, DmgTypes,
               ArmTypes, ManaTypes);
    Attributes(unsigned, unsigned, unsigned,
               unsigned, unsigned);
};

#endif // ATTRIBUTES_H
