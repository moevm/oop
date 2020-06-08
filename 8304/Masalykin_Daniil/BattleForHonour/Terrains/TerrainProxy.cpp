#include "TerrainProxy.h"

TerrainProxy::TerrainProxy(Terrain *terrain):
    terrain(terrain) {}

int TerrainProxy::getAbsorbMultiply(ArmorType type) {
    if (terrain != nullptr) {
        return terrain->getAbsorbMultiply(type);
    } else{
        return 1;
    }
}

int TerrainProxy::getDamageMultiply(WeaponType type) {
    if (terrain != nullptr) {
        return terrain->getDamageMultiply(type);
    } else{
        return 1;
    }
}

