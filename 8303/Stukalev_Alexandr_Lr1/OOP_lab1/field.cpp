#include "iostream"
#include "field.h"


Field::Field(int lengthY, int lengthX) :lengthY(10), lengthX(10), max_object_count(10), obj_count(0)
    {
        field = new Cell * [lengthY];
        for (int i = 0; i < lengthY; i++)
        {
            field[i] = new Cell[lengthX];

        }
    }

Field::Field(const Field& ref_obj) :lengthX(ref_obj.lengthX), lengthY(ref_obj.lengthY), max_object_count(ref_obj.max_object_count), obj_count(ref_obj.obj_count), field(new Cell*[ref_obj.lengthY])// и перемещение
    {
        //пустой obj
        field = new Cell * [lengthY];
        for (int i = 0; i < lengthY; i++)
        {
            field[i] = new Cell [lengthX];
            for (int j = 0; j < lengthX; j++)
            {
                field[i][j] = ref_obj.field[i][j];
            }
        }
    }

Field::Field(Field&& ref_obj) :lengthX(ref_obj.lengthX), lengthY(ref_obj.lengthY), max_object_count(ref_obj.max_object_count), obj_count(ref_obj.obj_count), field(new Cell* [ref_obj.lengthY])// и перемещение
    {
        field = new Cell * [lengthY];
        for (int i = 0; i < lengthY; i++)
        {
            field[i] = new Cell  [lengthX];
            for (int j = 0; j < lengthX; j++)
            {
                field[i][j] = ref_obj.field[i][j];
            }
            delete[](ref_obj.field[i]);
        }
        delete[](ref_obj.field);
    }

Field::~Field()
    {
        for (int i = 0; i < lengthY; i++)
        {
            delete[] field[i];
        }
        delete[] field;
    }



void Field::insert_Unit(Unit* obj)
    {
        if ((obj_count < max_object_count) && obj->x < this->lengthX && obj->y < this->lengthY && field[obj->y][obj->x].is_full == false)
        {
            field[obj->y][obj->x].unit = obj;
            field[obj->y][obj->x].is_full = true;
            obj_count++;
        }
    }

void Field::remove_Unit(Unit* obj)
    {
        if (obj != nullptr)
        {
            //Unit* tmp = field[obj->y][obj->x].unit;
            Cell new_cell;
            field[obj->y][obj->x] = new_cell;
            //delete tmp;
            obj_count--;
        }
    }
void Field::move_Unit(Unit* obj, int x, int y)
    {
        remove_Unit(obj);
        obj->move(x, y);
        insert_Unit(obj);
    }
void Field::print_field() const
    {
        for (int i = 0; i < this->lengthY; i++)
        {
            for (int j = 0; j < this->lengthX; j++)
            {
                if (field[i][j].is_full == false)
                {
                    std::cout << 0 << ' ';
                }
                else
                {
                    std::cout << field[i][j].unit->designation << ' ';
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
