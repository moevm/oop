#ifndef COMMANDPAR_H
#define COMMANDPAR_H

enum eLandscapeType
{
    CHAMPAIGN,
    FOREST,
    MOUNTAINS,
};

enum eBaseType
{
    NONE_BASE,
    HUMAN_BASE,
    HELL_BASE
};

enum eRequest
{
    NONE,
    GAME_INFO,
    BASE_INFO,
    UNIT_INFO,
    LAND_INFO,
    ITEM_INFO,
    ADD_UNIT,
    MOVE_UNIT,
    ATTACK_UNIT,
};

#endif // COMMANDPAR_H
