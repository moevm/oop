#ifndef LIBRARIES_H
#define LIBRARIES_H

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>



enum UnitType {
    ATT_SC,
    ATT_BS,
    SUP_SC,
    SUP_BS,
    SIM_SC,
    SIM_BS
};

enum BaseType {
    BASE = 6
};

enum LandType {
    OPEN,
    OPEN_B,
    VPN,
    VPN_B,
    FAST,
    FAST_B
};

enum NeutralType{
    CHEST = 7,
    KEYGEN,
    ANTIVIRUS,
    DATA
};

enum RequestType{
    GAME_INFO = 100,
    BASE_INFO,
    LAND_INFO,
    ITEMS_INFO,
    ADD,
    FIND,
    MOVE,
    GETXY,
    ATTACK
};

#endif // LIBRARIES_H
