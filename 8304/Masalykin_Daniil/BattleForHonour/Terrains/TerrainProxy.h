#ifndef BATTLEFORHONOUR_TERRAINPROXY_H
#define BATTLEFORHONOUR_TERRAINPROXY_H


#include "Terrain.h"
#include "../GameField/Point.h"

class TerrainProxy {

private:
    Terrain *terrain;
public:
    explicit TerrainProxy(Terrain *terrain);
    int getDamageMultiply(WeaponType type);
    int getAbsorbMultiply(ArmorType type);
};


#endif //BATTLEFORHONOUR_TERRAINPROXY_H
