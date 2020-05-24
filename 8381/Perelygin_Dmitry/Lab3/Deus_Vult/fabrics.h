#ifndef FABRICS_H
#define FABRICS_H
#include <vector>
#include "crusader.h"
#include "arab.h"
#include "arabarcher.h"
#include "crusaderarcher.h"
#include "knight.h"
#include "camelrider.h"

enum Warrior_ID;
// Иерархия классов игровых персонажей

class Fabrics
{


public:

    Fabrics() = default;

    virtual Unit* createWarrior( Warrior_ID id, int new_name, class Field *new_field, class Base* new_base ) = 0;

};

#endif // FABRICS_H
