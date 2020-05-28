#ifndef MYLITTLEGAME_NTRLSTRATEGY_H
#define MYLITTLEGAME_NTRLSTRATEGY_H

#endif //MYLITTLEGAME_NTRLSTRATEGY_H


enum class ObjEffectType{
    hp,range,power
};

struct ObjEffect{
    ObjEffectType type;
    int size;
};

struct Strategy{
    virtual  ObjEffect execute(int o) =0;
};

struct HealingStrategy: Strategy{
    ObjEffect execute(int o);
};

struct PowerStrategy: Strategy{
    ObjEffect execute(int o);
};

struct RangeStrategy: Strategy{
    ObjEffect execute(int o);
};