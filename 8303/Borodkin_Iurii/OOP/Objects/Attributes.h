#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

enum struct HpTypes : int
{
    ARCHER    = 1000, WIZARD   =  750,
    SWORDSMAN = 1500, SPEARMAN =  750,
    CENTAUR   =  750, PANZER   = 2000,
    BASE      = 50
};

enum struct RngTypes : unsigned
{
    ARCHER    = 3, WIZARD   = 2,
    SWORDSMAN = 1, SPEARMAN = 1,
    CENTAUR   = 1, PANZER   = 1,
    BASE      = 0
};

enum struct DmgTypes : unsigned
{
    ARCHER    = 100, WIZARD   = 250,
    SWORDSMAN = 150, SPEARMAN =  75,
    CENTAUR   =  50, PANZER   = 100,
    BASE      =   0
};

enum struct ArmTypes : unsigned
{
    ARCHER    = 100, WIZARD   =   0,
    SWORDSMAN = 250, SPEARMAN = 100,
    CENTAUR   =   0, PANZER   = 500,
    BASE      =   0
};

enum struct ManaTypes : unsigned
{
    ARCHER    = 0, WIZARD   = 500,
    SWORDSMAN = 0, SPEARMAN =   0,
    CENTAUR   = 0, PANZER   =   0,
    BASE      = 0
};

class Attributes
{
public:
    int health;
    unsigned range ;
    unsigned damage;
    unsigned armor ;
    unsigned mana  ;

    Attributes(HpTypes, RngTypes, DmgTypes,
               ArmTypes, ManaTypes);

    Attributes(int, unsigned, unsigned,
               unsigned, unsigned);

    Attributes operator+(const Attributes& attr);
};


#endif // ATTRIBUTES_H
