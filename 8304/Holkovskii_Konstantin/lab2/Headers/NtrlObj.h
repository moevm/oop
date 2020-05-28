#ifndef MYLITTLEGAME_NTRLOBJ_H
#define MYLITTLEGAME_NTRLOBJ_H
#include <vector>
#include "NtrlStrategy.h"
#endif //MYLITTLEGAME_NTRLOBJ_H


struct NtrlObj {
    virtual std::vector<char> who() = 0;
    virtual ObjEffect get() = 0;

};

struct Oasis : NtrlObj{
    std::vector<char> who() override;
    ObjEffect get() override;
    HealingStrategy str;
};

struct Crocodile : NtrlObj{
    std::vector<char> who() override;
    ObjEffect get() override;
    HealingStrategy str;
};

struct PowerStatue : NtrlObj{
    std::vector<char> who() override;
    ObjEffect get() override;
    PowerStrategy str;
};

struct RangeStatue : NtrlObj{
    std::vector<char> who() override;
    ObjEffect get() override;
    RangeStrategy str;
};