#include "iostream"
#include "field.h"


Field::Field(int lengthY, int lengthX) :lengthY(10), lengthX(10), max_object_count(10), obj_count(0),humanBase(nullptr),alienBase(nullptr)
    {
        field = new Cell * [lengthY];
        for (int i = 0; i < lengthY; i++)
        {
            field[i] = new Cell[lengthX];

        }
    }

Field::Field(const Field& ref_obj) :lengthX(ref_obj.lengthX), lengthY(ref_obj.lengthY), max_object_count(ref_obj.max_object_count), obj_count(ref_obj.obj_count), field(new Cell*[ref_obj.lengthY])// и перемещение
    {
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
        this->allUnitsDis();
        if ((obj_count < max_object_count) && obj->x < this->lengthX && obj->y < this->lengthY && field[obj->y][obj->x].is_full == false)
        {
            field[obj->y][obj->x].unit = obj;
            field[obj->y][obj->x].is_full = true;
            obj_count++;
        }
        obj->setChoose(true);
    }

void Field::remove_Unit(Unit* obj)
    {
        if (obj != nullptr)
        {
            Cell tmp;
            field[obj->y][obj->x] = tmp;
            obj_count--;
        }
    }
void Field::move_Unit(Unit* obj, int x, int y)
    {
        //field[obj->getY()][obj->getY()].land->interact(obj);
        if(!obj->canMove())
        {
                this->remove_Unit(obj);
                obj->move(x,y);
                this->insert_Unit(obj);
                //*(field[obj->y][obj->x].obj)>>obj;
                if(obj->getHealth() < 0)
                {
                    this->remove_Unit(obj);
                }
        }
        else
        {
            std::cout << "Can't move unit ";
            std::cout << " to cell (" << x << "," << y << ")" << std::endl;
        }
    }

void Field::print_field() const
    {
        for (int i = 0; i < this->lengthY; i++)
        {
            for (int j = 0; j < this->lengthX; j++)
            {
                if(j == 0 && i == 0)
                    std::cout << "H ";
                else if(i == this->getX() - 1 && j == this->getY() -1)
                    std::cout << "A ";
                else if (field[i][j].is_full == false)
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

void Field::allNeutral()
{
    for (int j = 0; j < this->getY(); j++)
    {
        for (int i = 0; i < this->getX(); i)
        {
            field[j][i].obj = new NoneObject();
        }
    }
}

int Field::getX() const
{
    return this->lengthX;
}

int Field::getY() const
{
    return this->lengthY;
}
void Field::create_ABase( int max_count, int health)
{
    Base* base = new Base( max_count, health, this->getX()-1,this->getY()-1);
    this->alienBase = base;
    field[base->x][base->y].AlienBase = base;
}
void Field::create_HBase( int max_count, int health)
{
    Base* base = new Base( max_count, health, 0, 0);
    this->humanBase = base;
    field[base->x][base->y].HumanBase = base;
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

void Field::moveAUnit(char wayToMove, Unit *unit)
{
    this->alienBase->move_unit(this,wayToMove,unit);
}

void Field::moveHUnit(char wayToMove, Unit *unit)
{
    this->humanBase->move_unit(this,wayToMove,unit);
}

bool Field::getIsMaxCount()
{
    if(this->obj_count < this->max_object_count)
        return true;
    return false;
}

bool Field::getIsAMaxCount()
{
    return alienBase->getIsMaxCount();
}

bool Field::getIsHMaxCount()
{
    return humanBase->getIsMaxCount();
}

bool Field::checkCell(int x, int y)
{
    if( x >= 0 && y >=0 && x < this->getX() && y < this->getY())
    {
        if(this->field[y][x].is_full == false)
            return true;
    }
    return false;
}

bool Field::checkUnit(int x, int y)
{
    if(this->field[y][x].is_full == true)
        return true;
    return false;
}

bool Field::checkHBase(int x, int y)
{
    if(x == 0 && y == 0 )
        return true;
    return false;
}
bool Field::checkABase(int x, int y)
{
    if(x == this->getX() - 1 && y == this->getY() - 1)
        return true;
    return false;
}

void Field::createAUnit(char unit)
{
    this->alienBase->create_unit(this,unit,'A');
}

void Field::createHUnit(char unit)
{
    this->humanBase->create_unit(this,unit,'H');
}

void Field::allUnitsDis()
{
    for(int j = 0; j < this->getY(); j++)
    {
        for(int i = 0; i < this->getX(); i++)
        {
            if(this->field[i][j].is_full)
            {
                this->field[i][j].unit->setChoose(false);
            }
        }
    }
}

bool Field::checkAleinBase()
{
    if(this->alienBase == nullptr)
        return false;
    return true;
}

bool Field::checkHumanBase()
{
    if(this->humanBase == nullptr)
        return false;
    return true;
}

Unit* Field::getAChoosen()
{
    for(int j = 0; j < this->getY() - 1; j++)
    {
        for(int i = 0; i < this->getX() - 1; i++)
        {
            if(this->field[j][i].is_full && this->field[j][i].unit->getArmy()== 'A' && this->field[j][i].unit->getChoose() == true)
            {
                return this->field[j][i].unit;
            }
        }
    }
    return nullptr;
}

Unit* Field::getHChoosen()
{
    for(int j = 0; j < this->getY() - 1; j++)
    {
        for(int i = 0; i < this->getX() - 1; i++)
        {
            if(this->field[j][i].is_full && this->field[j][i].unit->getArmy()== 'H' && this->field[j][i].unit->getChoose() == true)
            {
                return this->field[j][i].unit;
            }
        }
    }
    return nullptr;
}

Base* Field::getABase()
{
    return this->alienBase;
}

Base* Field::getHBase()
{
    return this->humanBase;
}

Unit* Field::getUnit(int x, int y)
{
    if(this->field[y][x].is_full == true)
        return this->field[y][x].unit;
    return nullptr;
}
