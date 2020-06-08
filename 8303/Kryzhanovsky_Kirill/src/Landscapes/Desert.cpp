//
// Created by therealyou on 10.03.2020.
//

#include "Desert.h"

int Desert::getAbsorptionFactor(UnitsType unit) {
    switch (unit){
        case UnitsType::ELF:
            return 11;
        case UnitsType::WITCH:
            return 10;
        case UnitsType::PEON:
            return 12;
        case UnitsType::SHOOTER:
            return 11;
        case UnitsType::TROLL:
            return 12;
        case UnitsType::GOBLIN:
            return 12;
    }
}

int Desert::getSlowFactor(UnitsType unit) {
    switch (unit){
        case UnitsType::ELF:
        case UnitsType::WITCH:
        case UnitsType::PEON:
        case UnitsType::SHOOTER:
        case UnitsType::TROLL:
        case UnitsType::GOBLIN:
            return 10;
    }
}

Desert::Desert() {

}
