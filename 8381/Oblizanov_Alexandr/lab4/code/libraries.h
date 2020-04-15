#ifndef LIBRARIES_H
#define LIBRARIES_H

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <fstream>

#define LOGFILE "log.txt"

enum LoggerType {
    NO_LOGGER,
    TO_TERMINAL,
    TO_FILE
};

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

enum LogEvent{
    USER_GAME_INFO = 200,
    USER_BASE_INFO,
    USER_LAND_INFO,
    USER_ITEMS_INFO,
    USER_ITEM_INFO,
    USER_BASE_ADD,
    USER_UNIT_ADD,
    USER_NEUTRAL_ADD,
    USER_MOVE,
    USER_ATTACK,

    GAME_CREATE,
    BASE_ADD,
    NEUTRAL_ADD,
    UNIT_ADD,
    BASE_UPDATE,
    COUNTER_UPDATE,
    UNIT_ATTACK,
    UNIT_MOVE
};

enum LogType{
    SHORT = 300,
    FULL
};

#endif // LIBRARIES_H
