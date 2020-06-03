
#ifndef TypeСonstants_hpp
#define TypeСonstants_hpp
enum eTask
{
    ADD_ROOM,
    ADD_PLAYER,
    ADD_OBJ,
    MOVE,
    UPD_LAND,
    GET_FULL,
    SAVE_ROOM,
    LOAD_ROOM,
    ROOMS_LIST,
};

enum eLandscapeType
{
    FOREST,
    MOUNTAIN,
    PLAIN,
    SWAMP,

};

enum eCombNeutType
{
    COMB_OBJ,
    NEUT_OBJ,
};

enum eObjectType
{
    BASE,
    ARCH_TANK,
    ARCH_DPS,
    INF_TANK,
    INF_DPS,
    CAV_TANK,
    CAV_DPS,
    GEN_GOLD,
    GEN_SAWMILL,
    GEN_FARM,
};

enum eResourceType
{
    GOLD,
    WOOD,
    FOOD,
};

enum eRule
{
    RULE1,
    RULE2,
};

#endif /* TypeСonstants_hpp */
