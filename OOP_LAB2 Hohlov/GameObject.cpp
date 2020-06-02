//
// Created by Глебушунок on 15.03.2020.
//

#include "GameObject.h"
std::ostream &operator<<(std::ostream &stream, const GameObject &object) {

    object.print(stream);
}