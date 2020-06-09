class UnitHQ : public UnitBase
{
public:
    const static int
                    pierce = 0,
                    armor = 75,
                    damage = 0,
                    movementRange = 0;
    const std::string
                    name = "Headquarters";
    UnitHQ( TFaction argFaction, int X, int Y ) : UnitBase( argFaction, X, Y ) {}
};
