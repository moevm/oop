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
            field[0][0].base->update(obj);
        }
    }
void Field::move_Unit(Unit* obj, int x, int y)
    {
        field[y][x].land->interact(obj);
        if(obj->canMove())
        {
                field[obj->y][obj->x].unit = nullptr;
                obj->move(x,y);
                field[obj->y][obj->x].unit = obj;
                *(field[obj->y][obj->x].obj)>>obj;
                if(obj->getHealth() < 0)
                {
                    this->remove_Unit(obj);
                }

            }
            else {
                std::cout << "Can't move unit ";
                std::cout << " to cell (" << x << "," << y << ")" << std::endl;
            }
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
                /*if(field[i][j].base)
                {
                    std::cout << "B ";
                }*/
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
Base* Field::create_Base( int max_count, int health)
{
    Base* base = new Base( max_count, health);
    field[base->x][base->y].base = base;
    return base;
}

void Field::create_Landscape()
{
    for (int i= 0; i < this->lengthY; i++)
    {
        for (int j = 0; j < this->lengthX;j++)
        {
            this->field[i][j].land = new PlainProxy();
        }
    }

    for (int j = 0; j < 5;j++)
    {

        this->field[5][j].land = new MountainProxy();
    }

    for (int j = 5; j < 10;j++)
    {

        this->field[5][j].land = new RiverProxy();
    }
}

void Field::show_Landscape()
{
    for (int i = 0; i < this->lengthY; i++)
    {
        for (int j = 0; j < this->lengthX;j++)
        {
            cout << field[i][j].land->getName() << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void Field::create_Neutral(int x, int y, char name)
{
    if( name == 'M' )
        field[y][x].obj = new FieldMine();
    else if( name == 'V' )
        field[y][x].obj = new Village();
    else if( name == 'W' )
        field[y][x].obj = new Workshop();
    else if( name == 'A' )
        field[y][x].obj = new Altar();
}

void Field::show_Neutral()
{
    for (int i = 0; i < this->lengthY; i++)
    {
        for (int j = 0; j < this->lengthX;j++)
        {
            if(field[i][j].obj != nullptr)
            {
            cout << field[i][j].obj->getName() << " ";
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}
