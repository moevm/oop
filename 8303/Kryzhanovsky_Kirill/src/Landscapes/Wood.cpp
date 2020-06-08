//
// Created by therealyou on 10.03.2020.
//

#include "Wood.h"

int Wood::getAbsorptionFactor(UnitsType unit) {
    switch (unit){
        case UnitsType::ELF:
            return 13;
        case UnitsType::WITCH:
            return 11;
        case UnitsType::PEON:
            return 15;
        case UnitsType::SHOOTER:
            return 11;
        case UnitsType::TROLL:
            return 15;
        case UnitsType::GOBLIN:
            return 16;
    }
}

int Wood::getSlowFactor(UnitsType unit) {
    switch (unit){
        case UnitsType::ELF:
            return 12;
        case UnitsType::WITCH:
            return 11;
        case UnitsType::PEON:
            return 13;
        case UnitsType::SHOOTER:
            return 12;
        case UnitsType::TROLL:
            return 13;
        case UnitsType::GOBLIN:
            return 14;
    }
}

Wood::Wood() {

}
