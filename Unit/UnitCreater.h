//
// Created by Jack on 08/03/2020.
//

#ifndef OOP1_3_UNITCREATER_H
#define OOP1_3_UNITCREATER_H

#include "Unit.h"
#include "ArmoredCar.h"
#include "Tank.h"
#include "Rifleman.h"
#include "Medic.h"
#include "Sniper.h"
#include "RocketLauncher.h"
#include <iostream>
    //                             Абстрактные методы
    class Creater {  // абстрактный метод
        virtual Unit* create(int x, int y) = 0;
    };

    class TankCreater : public Creater {
    public:
        Unit* create(int x, int y) {
            return new Tank(x,y);
        }
    };

    class ArmoredCarCreater : public Creater {
    public:
        Unit* create(int x, int y) {
            return new ArmoredCar(x,y);
        }
    };

    class RiflemanCreater : public Creater {
    public:
        Unit* create(int x, int y) {
            return new Rifleman(x,y);
        }
    };

    class MedicCreater : public Creater {
    public:
        Unit* create(int x, int y) {
            return new Medic(x,y);
        }
    };

    class SniperCreater : public Creater {
    public:
        Unit* create(int x, int y) {
            return new Sniper(x,y);
        }
    };

    class RocketLauncherCreater : public Creater {
    public:
        Unit* create(int x, int y) {
            return new RocketLauncher(x,y);
        }
    };


#endif //OOP1_3_UNITCREATER_H
