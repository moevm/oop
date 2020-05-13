#ifndef MOVEMEDIATOR_H
#define MOVEMEDIATOR_H

class Field;
class Unit;

class MoveMediator
{
private:
    Field* field;
    Unit* fieldItem;
public:
    MoveMediator(Field*, Unit*);
    void movObj(Unit*, int, int);

};

#endif //MOVEMEDIATOR_H
