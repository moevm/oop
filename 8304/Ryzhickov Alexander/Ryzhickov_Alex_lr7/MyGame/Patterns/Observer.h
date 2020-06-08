//
// Created by Alex on 12.04.2020.
//

#ifndef GAME_OBSERVER_H
#define GAME_OBSERVER_H

#include "../Units/Unit.h"

namespace GameUnit {
    class Observer {
    public:
        virtual void handleEvent(const Unit &unit) = 0;
    };
}
#endif //GAME_OBSERVER_H
