#ifndef OOP_UNITPAR_H
#define OOP_UNITPAR_H

/*------------------------------------
           UNITS PARAMETERS
--------------------------------------*/

/**
 * @brief The eUnitsType enum
 * In case of adding a new type of units,
 * it is necessary to reflect the changes
 * in the converter "enum->std::string"
 */
enum eUnitsType
{
    VALUES_FIRST = 0,

    NONE_UNIT,

    CANNON_FODDER,
    INFANTRY,
    SHOOTER,
    WIZARD,
    CAVALRY,

    COMPOSITE_UNIT,

    VALUES_END
};

#define TYPES_OF_UNIT 5

        /* MOVEMENT RANGE */
#define PEASANT_MOVEMENT_RANGE 2
#define SWORDSMAN_MOVEMENT_RANGE 1
#define ARCHER_MOVEMENT_RANGE 2
#define MAGICIAN_MOVEMENT_RANGE 1
#define KNIGHT_MOVEMENT_RANGE 3

#define HECK_MOVEMENT_RANGE 1
#define IFRIT_MOVEMENT_RANGE 2
#define SUCCUBUS_MOVEMENT_RANGE 2
#define DEMON_MOVEMENT_RANGE 1
#define CERBERUS_MOVEMENT_RANGE 2

#endif //OOP_UNITPAR_H
