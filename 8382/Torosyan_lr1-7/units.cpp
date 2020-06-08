#include <string>
#include <cmath>

#ifndef LOG
#define LOG
#include "log.cpp"
#endif

class UnitBase
{
public:
    std::string     faction;
     int
                    pierce = 0, armor = 0, damage = 0, movementRange = 0, attackRange = 0;
     std::string
                    name = "thats a bug mah friend";
    int             HP;
    int             x, y;

    UnitBase( std::string argFaction, int X, int Y ) :
              faction(argFaction), x(X), y(Y)
            {
                HP = 100;
            };
};

class UnitSniper : public UnitBase
{
public:
    UnitSniper( std::string argFaction, int X, int Y ) : UnitBase( argFaction, X, Y )
    {
        pierce = 5;
        armor = 5;
        damage = 75;
        movementRange = 2;
        attackRange = 3;
         name = "Sniper squad";
    }
};

class UnitAntiTank : public UnitBase
{
public:
   UnitAntiTank( std::string argFaction, int X, int Y ) : UnitBase( argFaction, X, Y )
   {
        pierce = 40;
        armor = 5;
        damage = 70;
        movementRange = 1;
        attackRange = 3;
        name = "Anti-tank team";
   }
};

class UnitIFV : public UnitBase
{
public:
    UnitIFV( std::string argFaction, int X, int Y ) : UnitBase( argFaction, X, Y )
    {
        pierce = 20;
        armor = 25;
        damage = 55;
        movementRange = 4;
        attackRange = 2;
        name = "IFV platoon";
    }
};

class UnitTank : public UnitBase
{
public:

    UnitTank( std::string argFaction, int X, int Y ) : UnitBase( argFaction, X, Y )
    {
        pierce = 40;
        armor = 40;
        damage = 75;
        movementRange = 3;
        attackRange = 4;
        name = "Heavy tank platoon";
    }
};

class UnitBomber : public UnitBase
{
public:
    UnitBomber( std::string argFaction, int X, int Y ) : UnitBase( argFaction, X, Y )
    {
        pierce = 60;
        armor = 10;
        damage = 150;
        movementRange = 4;
        attackRange = 1;
        name = "Heavy bomber";
    }
};

class UnitInterceptor : public UnitBase
{
public:
    UnitInterceptor( std::string argFaction, int X, int Y ) : UnitBase( argFaction, X, Y )
    {
        pierce = 90;
        armor = 20;
        damage = 90;
        movementRange = 5;
        attackRange = 3;
        name = "Interceptors wing";
    }
};

class UnitHQ : public UnitBase
{
public:
    Logger baseLog;
    UnitBase** unitList;
    int unitCount = 0;

    UnitHQ( std::string argFaction, int X, int Y, int UnitCap ) : UnitBase( argFaction, X, Y), baseLog("base.log")
    {
        pierce = 0;
        armor = 40;
        damage = 0;
        movementRange = 0;
        attackRange = 0;
        name = "Headquarters";
        HP = 200;
        unitList = new UnitBase * [UnitCap];
    };

    ~UnitHQ()
    {
        delete[] unitList;
    }

    void addUnit( UnitBase* u )
    {
        baseLog.HQAddUnitLog( u->faction, u->name );
        unitList[unitCount++] = u;
    };

    void removeUnit( UnitBase* u )
    {
        baseLog.HQLoseUnitLog( u->faction, u->name );
        int pos = 0;
        while( unitList[pos] != u && pos++ < unitCount);
        for(;pos < unitCount; pos++)
            unitList[pos] = unitList[pos+1];
    }

    void onUnitDie(UnitBase* u )
    {
        removeUnit( u );
    };
    void onUnitCreate(UnitBase* u )
    {
        addUnit( u );
    };

    UnitSniper* makeSniper(int X, int Y){
        UnitSniper* tmp = new UnitSniper(faction, X, Y);
        addUnit( tmp );
        return tmp;
    };
    UnitAntiTank* makeAntiTank(int X, int Y){
        UnitAntiTank* tmp = new UnitAntiTank(faction, X, Y);
        addUnit( tmp );
        return tmp;
    };
    UnitIFV* makeIFV(int X, int Y){
        UnitIFV* tmp = new UnitIFV(faction, X, Y);
        addUnit( tmp );
        return tmp;
    };
    UnitTank* makeTank(int X, int Y){
        UnitTank* tmp = new UnitTank(faction, X, Y);
        addUnit( tmp );
        return tmp;
    };
    UnitBomber* makeBomber(int X, int Y){
        UnitBomber* tmp = new UnitBomber(faction, X, Y);
        addUnit( tmp );
        return tmp;
    };
    UnitInterceptor* makeInterceptor(int X, int Y){
        UnitInterceptor* tmp = new UnitInterceptor(faction, X, Y);
        addUnit( tmp );
        return tmp;
    };
};

class EntityArmor : public UnitBase
{
public:
    EntityArmor( int X, int Y ) : UnitBase( "NEUTRAL", X, Y )
    {
        pierce = 0;
        armor = 5;
        damage = 0;
        movementRange = 0;
        attackRange = 0;
         name = "Additional armor";
    }
};

class EntityAmmo : public UnitBase
{
public:
    EntityAmmo( int X, int Y ) : UnitBase( "NEUTRAL", X, Y )
    {
        pierce = 0;
        armor = 5;
        damage = 0;
        movementRange = 0;
        attackRange = 0;
         name = "Armor-piercing ammo";
    }
};

class EntityOptics : public UnitBase
{
public:
    EntityOptics( int X, int Y ) : UnitBase( "NEUTRAL", X, Y )
    {
        pierce = 0;
        armor = 5;
        damage = 0;
        movementRange = 0;
        attackRange = 0;
         name = "Improved optics";
    }
};

class EntityMedkit : public UnitBase
{
public:
    EntityMedkit( int X, int Y ) : UnitBase( "NEUTRAL", X, Y )
    {
        pierce = 0;
        armor = 5;
        damage = 0;
        movementRange = 0;
        attackRange = 0;
         name = "Medi-kits";
    }
};
/*
* INF: sniper, anti-tank
* VEH: IFV, AA
* AIR: bomber, intercept
*/
