//
// Created by therealyou on 11.03.2020.
//

#include "Medicine.h"

Medicine::Medicine(int x, int y, int buffValue) :
Object(x, y, buffValue, ObjectsType::MEDICINE) {

}

char Medicine::getChar() {
    return 'M';
}
