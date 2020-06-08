//
// Created by therealyou on 10.03.2020.
//

#include "Mountain.h"

int Mountain::getAbsorptionFactor(UnitsType unit) {
    switch (unit){
        case UnitsType::ELF:
            return 14;
        case UnitsType::WITCH:
            return 12;
        case UnitsType::PEON:
            return 16;
        case UnitsType::SHOOTER:
            return 12;
        case UnitsType::TROLL:
            return 16;
        case UnitsType::GOBLIN:
            return 16;
    }
}

int Mountain::getSlowFactor(UnitsType unit) {
    switch (unit){
        case UnitsType::ELF:
            return 13;
        case UnitsType::WITCH:
            return 12;
        case UnitsType::PEON:
            return 14;
        case UnitsType::SHOOTER:
            return 13;
        case UnitsType::TROLL:
            return 14;
        case UnitsType::GOBLIN:
            return 14;
    }
}

Mountain::Mountain() {

}
