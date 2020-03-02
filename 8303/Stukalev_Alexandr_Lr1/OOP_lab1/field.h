#ifndef FIELD_H
#define FIELD_H
#include "units.h"
using namespace  std;

struct Cell
{
    bool is_full = false;
    Unit* unit = nullptr;

};

class Field
{
    friend class FieldIterator;
private:
    const int lengthX;
    const int lengthY;
    Cell** field = nullptr;
    const int max_object_count;
    int obj_count;
public:
    Field(int lengthY, int lengthX);
    Field(const Field& ref_obj);
    Field(Field&& ref_obj);
    ~Field();
    void insert_Unit(Unit* obj);
    void remove_Unit(Unit* obj);
    void move_Unit(Unit* obj, int x, int y);
    void print_field() const;
};


#endif // FIELD_H
