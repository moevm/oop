//
// Created by egor on 15.03.2020.
//

#include "Field.h"

int Field::getWidth() const { return  width; }
int Field::getHeight() const { return height; }


Field::Field(int size) : width(size), height(size)
{
    map = new Unit** [size];
    for (int y = 0; y < size; y++)
    {
        map[y] = new Unit* [size];
        for (int x = 0; x < size; x++)
        {
            map[y][x] = nullptr;
        }
    }
}


Field::Field(int height, int width) : height(height), width(width)
{
    map = new Unit** [height];
    for (int y = 0; y < height; y++)
    {
        map[y] = new Unit* [width];
        for (int x = 0; x < width; x++)
        {
            map[y][x] = nullptr;
        }
    }
}


Field::Field(const Field& other) : height(other.height), width(other.width), maxUnit(other.maxUnit)
{
    map = new Unit** [height];
    for (int y = 0; y < height; y++)
    {
        map[y] = new Unit* [width];
        for (int x = 0; x < width; x++)
        {
            map[y][x] = other.map[y][x];
        }
    }
}


Field& Field::operator=(const Field &other)
{
    if (&other != this) {
        for (int y = 0; y < height; y++)
            delete[] map[y];

        delete[] map;

        this->height = other.height;
        this->width = other.width;
        this->maxUnit = other.maxUnit;

        map = new Unit **[height];
        for (int y = 0; y < height; y++) {
            map[y] = new Unit *[width];
            for (int x = 0; x < width; x++) {
                map[y][x] = other.map[y][x];
            }
        }
    }
    return *this;
}


Field::Field(Field&& other) : height(other.height), width(other.width), map(other.map), maxUnit(other.maxUnit)
{
    other.map = nullptr;
    other.width = 0;
    other.height = 0;
    other.maxUnit = 0;
}


Field& Field::operator=(Field &&other)
{
    if (&other != this) {
        for (int y = 0; y < height; y++)
            delete[] map[y];

        delete[] map;

        this->map = other.map;
        this->height = other.height;
        this->width = other.width;
        this->maxUnit = other.maxUnit;

        other.map = nullptr;
        other.height = 0;
        other.width = 0;
        other.maxUnit = 0;
    }
    return *this;
}


void Field::addObject(Unit* object, int x, int y)
{
    if (x >= width || y >= height || x < 0 || y < 0)
    {
        std::cout << "Границы указаны не правильно" << std::endl;
        return;
    }

    if (!map[y][x] || maxUnit == 0)
    {
        map[y][x] = object;
        maxUnit--;
        object->coordinates = Point(x, y);
    } else {
        std::cout << "На поле уже стоит юнит или юнитов слишком много" << std::endl;
        return;
    }


}


void Field::deleteObject(int x, int y)
{
    if (x >= width || y >= height || x < 0 || y < 0)
    {
        std::cout << "Границы указаны не правильно" << std::endl;
        return;
    }
    if (map[y][x])
    {
        map[y][x]->~Unit();
        delete map[y][x];
        map[y][x] = nullptr;
        maxUnit++;
    } else {
        std::cout << "Тут ничего нет" << std::endl;
    }
}

void Field::deleteObject(Point &p)
{
    deleteObject(p.x, p.y);
}


void Field:: deleteObject(Unit *object)
{
    deleteObject(object->coordinates.x, object->coordinates.y);
}


void Field::moveObject(Point p1, Point p2)
{
    if (p1.x >= width || p1.y >= height || p1.x < 0 || p1.y < 0)
    {
        std::cout << "Границы указаны не правильно" << std::endl;
        return;
    }
    if (p2.x >= width || p2.y >= height || p2.x < 0 || p2.y < 0)
    {
        std::cout << "Границы указаны не правильно" << std::endl;
        return;
    }
    if (map[p1.y][p1.x] && !map[p2.y][p2.x])
    {
        map[p2.y][p2.x] = map[p1.y][p1.x];
        map[p2.y][p2.x]->coordinates = p2;

        map[p1.y][p1.x] = nullptr;
    } else {
        std::cout << "Нечего перемещать или место занято" << std::endl;
    }
}


void Field::moveObject(Unit *object, Point p2)
{
    Point p1 = object->getCoordinates();
    moveObject(p1, p2);
}


Unit * Field::getObject(Point &p) const {
    if (p.y < height && p.x < width)
        return map[p.y][p.x];
    return nullptr;
}


void Field::print_type(Point p) const
{
    std::string str = getObject(p)->type();

    if (str == "Archer")
    {
        std::cout << "A";
    }
    if (str == "Wizard")
    {
        std::cout << "W";
    }
    if (str == "HeavyCavalry")
    {
        std::cout << "HC";
    }
    if (str == "SpearHorse")
    {
        std::cout << "SH";
    }
    if (str == "LongSwordMan")
    {
        std::cout << "LS";
    }
    if (str == "ShildMan")
    {
        std::cout << "SM";
    }

}


void Field::print() const
{

    std::cout.width(5);
    for (int i = 0; i < getWidth(); i++)
    {
        std::cout.width(5);
        std::cout << i;
    }

    for(int y = 0; y < height; y++) {
        std::cout << std::endl;
        std::cout << y;
        for (int x = 0; x < width; x++) {

            if (x == 0)
            {
                std::cout.width(4);
            }else {
                std::cout.width(5);
            }

            if (!map[y][x])
            {
                std::cout << 'H';
            } else
            {
                print_type(Point(x, y));
            }
        }
    }

    std::cout << std::endl << std::endl << std::endl << std::endl;
}


Field::~Field()
{
    for (int y = 0; y < height; y++)
        delete [] map[y];

    delete [] map;
}