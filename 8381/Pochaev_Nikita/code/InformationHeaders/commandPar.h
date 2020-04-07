#ifndef COMMANDPAR_H
#define COMMANDPAR_H

enum LandscapeType
{
    CHAMPAIGN,
    FOREST,
    MOUNTAINS,
};

enum BaseType
{
    HUMAN_BASE = 80,
    HELL_BASE
};

enum Request
{
    GAME_INFO = 100,
    BASE_INFO,
    LAND_INFO,
    ITEMS_INFO,
    ADD,
    MOVE,
    ATTACK,
};

#endif // COMMANDPAR_H
