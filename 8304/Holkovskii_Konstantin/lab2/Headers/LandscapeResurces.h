#ifndef MYLITTLEGAME_LANDSCAPERESURCES_H
#define MYLITTLEGAME_LANDSCAPERESURCES_H

#endif //MYLITTLEGAME_LANDSCAPERESURCES_H

enum class LandscapeTypes{
    Grass, Mount, Dust
};

enum class LandEffectType{
    hp,range,power,noeffect
};

struct LandEffect{
    LandEffectType type;
    int size;
};