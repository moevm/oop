/*#ifndef BASE_H
#define BASE_H

#include "units.h"
#include "composit.h"
#include "observer.h"

class Field;

class Base: public Observer
{
    friend class Field;
private:
    int health;
    int x,y;
    int count, max_count;
    char designation;
    Field * field;
    Composit* comp_unit;
    HumanArmyFactory hu_army;
    AlienArmyFactory al_army;
    Base(Field* fieldb,int max_count, int x,int y, int health);
public:
    void remove_unit(Unit* unit);
    void create_unit(char name, char army);
    void update(Subject* subject);
};


#endif // BASE_H*/
