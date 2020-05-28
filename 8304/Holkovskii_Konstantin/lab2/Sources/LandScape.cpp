
#include "../Headers/LandScape.h"

ProxyLandscape::ProxyLandscape(LandscapeTypes type) {
    switch(type){
        case LandscapeTypes::Grass:
            landscape = std::make_shared<Grass>();
            break;
        case LandscapeTypes::Dust:
            landscape = std::make_shared<Dust>();
            break;
        case LandscapeTypes::Mount:
            landscape = std::make_shared<Mount>();
            break;
    }
}

void ProxyLandscape::execute(std::unique_ptr<Unit> &unit) {
    landscape->execute(unit);
}

void Grass::execute(std::unique_ptr<Unit> &unit) {
    if(unit->name == 'K' || unit->name == 'S')
        unit->effect = {LandEffectType::power, 20};
}

void Mount::execute(std::unique_ptr<Unit> &unit) {
    if(unit->name == 'A' || unit->name == 'R')
        unit->effect = {LandEffectType::range, 1};
}

void Dust::execute(std::unique_ptr<Unit> &unit) {
    unit->effect = {LandEffectType::range, -1};
}
