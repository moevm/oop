
#include "../Headers/NtrlStrategy.h"

ObjEffect HealingStrategy::execute(int o) {
    return {ObjEffectType::hp, o};
}


ObjEffect PowerStrategy::execute(int o) {
    return {ObjEffectType::power, o};
}

ObjEffect RangeStrategy::execute(int o) {
    return {ObjEffectType::range, o};
}
