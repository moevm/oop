//
// Created by therealyou on 16.03.2020.
//

#include "LandscapeProxy.h"

LandscapeProxy::LandscapeProxy(Landscape *landscape) : landscape(landscape){
}

int LandscapeProxy::getAbsorptionFactor(UnitsType unit) {
    if (landscape){
        return landscape->getAbsorptionFactor(unit);
    }
    return 1;
}

int LandscapeProxy::getSlowFactor(UnitsType unit) {
    if (landscape){
        return landscape->getSlowFactor(unit);
    }
    return 1;
}
