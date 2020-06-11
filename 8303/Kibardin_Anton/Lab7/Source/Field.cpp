//
// Created by anton on 16.02.2020.
//

#include <iostream>
#include "Field.h"
#include <ctime>
Field::Field(int x, int y, Adapter* adapter1, int mode) :X(x), Y(y), matrix(new Cell*[X]), objectsCounter(0), maxObjectsOnField(x*y), adapter(adapter1), gameMode(mode)
, base1(nullptr), base2(nullptr), base3(nullptr), unit1(nullptr), unit2(nullptr), unit3(nullptr){
    for(int i = 0; i < X; i++) {
        matrix[i] = new Cell[Y];
        for(int j = 0; j < Y; j++)
        {
            matrix[i][j].setCharacter(nullptr);
            matrix[i][j].setBase(nullptr);

            int value = (i + j)%3;
            switch (value)
            {
                case 0:
                    matrix[i][j].setLandscape(new Grass);
                    break;
                case 1:
                    matrix[i][j].setLandscape(new Mountains);
                    break;
                case 2:
                    matrix[i][j].setLandscape(new Forest);
                    break;
            }

            value = (i + j)%4;
            switch (value)
            {
                case 0:
                    matrix[i][j].setNeutral(new ForcePortion);
                    break;
                case 1:
                    matrix[i][j].setNeutral(new Stew);
                    break;
                case 2:
                    matrix[i][j].setNeutral(new Poison);
                    break;
                case 3:
                    matrix[i][j].setNeutral(new RangePortion);
                    break;
            }
        }
    }
    ////////////////////////////////////////////////////////
    /*base1 = setBase(0,0,5, 1, 100);
    base2 = setBase(0,3,5, 2, 100);
    base3 = setBase(3,0,5, 3, 100);
    base1->createUnit('d', "dwarf1");
    base2->createUnit('d', "dwarf2");
    base3->createUnit('d', "dwarf3");*/
    ///////////////////////////////////////////////////////
}

Field::Field(Adapter* adapter1):Field(0,0, adapter1, 1) {}

Field::~Field()
{
    if(matrix)
    {
        for(int i = 0; i < X; i++)
            if(matrix + i)
                delete[] matrix[i];
        delete[] matrix;
    }
}

bool Field::addUnit(Unit *Object, int x, int y, std::string name) {
    if(checkPoint(x,y) && !matrix[x][y].getCharacter() &&  objectsCounter < maxObjectsOnField && matrix[x][y].isAvailable(Object)) {
        matrix[x][y].setCharacter(Object);
        objectsCounter++;
        Object->setX(x);
        Object->setY(y);
        Object->setName(name);
        adapter->setUnit(Object);
        return true;
    }
    return false;
}



int Field::getObjectCounter() const{
    return objectsCounter;
}

void Field::deleteUnit(Unit *Object) {
    for(FieldIterator iter(this); iter != nullptr; iter++)
        if((*iter)->unit == Object)
        {
            adapter->deleteUnit((*iter)->unit);
            (*iter)->clearCell();
        }
    objectsCounter--;
}

void Field::moveUnit(Unit *Object, int x, int y) {
    if(checkPoint(x,y) && matrix[x][y].isAvailable(Object))
    {
        //deleteUnit(Object);
        matrix[Object->getX()][Object->getY()].clearCell();
        matrix[x][y].landscape->impact(Object);
        matrix[x][y].neutral->getEffect(Object);
        Object->setX(x);
        Object->setY(y);
        matrix[x][y].unit = Object;
        //addUnit(Object, x,y, Object->getName());
        adapter->move(Object);
    } else
        throw LogicException("can't move at this position", std::to_string(x) + " " + std::to_string(y));
}

void Field::print() const{
    printf("--------Units-----\n");
    if(matrix == nullptr)
    {
        printf("------------------\n");
        return;
    }
    for(int i = 0; i < X;i++){
        for(int j = 0; j < Y; j++)
            if(matrix[i][j].getCharacter() != nullptr)
                std::cout << matrix[i][j].getCharacter()->getClass() << " ";
            else
            {
                if(matrix[i][j].base != nullptr)
                {
                    std::cout << "@ ";
                }
                else
                    std::cout << ". ";
            }
        std::cout << std::endl;
    }
    printf("------------------\n");
}

bool Field::checkPoint(int x, int y) const {
    return x < X && y < Y && x >= 0 && y >= 0;
}

int Field::getX() const {
    if(matrix != nullptr)
        return X;
    return -1;
}

int Field::getY() const {
    if(matrix != nullptr)
        return Y;
    return -1;
}

Field::Field(const Field& obj) : Field(obj.X,obj.Y, obj.adapter, obj.gameMode)
{
    objectsCounter = obj.objectsCounter;
    for(int i = 0; i < X; i++)
        for(int j = 0; j < Y; j++)
            this->matrix[X][Y] = obj.matrix[X][Y];
}

Field::Field(Field&& obj):X(obj.X), Y(obj.Y), matrix(nullptr), maxObjectsOnField(X*Y), objectsCounter(0), adapter(obj.adapter)
, base1(nullptr), base2(nullptr), base3(nullptr), unit1(nullptr), unit2(nullptr){
    std::swap(matrix, obj.matrix);
    std::swap(objectsCounter, obj.objectsCounter);
    std::swap(base1, obj.base1);
    std::swap(base2, obj.base2);
    std::swap(base3, obj.base3);
    std::swap(unit1, obj.unit1);
    std::swap(unit2, obj.unit2);

}

Field& Field::operator= (const Field& obj){
    this->X = obj.X;
    this->Y = obj.Y;
    this->objectsCounter = obj.objectsCounter;
    this->adapter = obj.adapter;
    this->maxObjectsOnField = obj.maxObjectsOnField;
    this->base1 = obj.base1;
    this->base2 = obj.base2;
    this->base3 = obj.base3;
    this->unit1 = obj.unit1;
    this->unit2 = obj.unit2;
    this->unit3 = obj.unit3;
    this->matrix = new Cell* [obj.X];
    for (int i = 0; i < X; i++){
        matrix[i] = new Cell[Y];
        for (int j = 0; j < Y; j++)
            matrix[i][j] = obj.matrix[i][j];
    }
    return *this;
}

Base* Field::setBase( int x, int y, int maxObjects, int baseNumber, int health = 100) {
    Base* tmp = nullptr;
    if(checkPoint(x,y))
    {
        tmp = new Base(this, x, y, maxObjects, baseNumber, health);
        matrix[x][y].base = tmp;
        if(baseNumber == 1)
        {
            base1 = tmp;
        }
        else if(baseNumber == 2)
        {
            base2 = tmp;
        }
        else if(baseNumber == 3)
        {
            base3 = tmp;
        }
        objectsCounter++;
        adapter->setBase(tmp);
        return tmp;
    }
    return nullptr;
}

void Field::printLandscape() const {
    printf("-----Landscape----\n");
    if(matrix == nullptr)
    {
        printf("------------------\n");
        return;
    }
    for(int i = 0; i < X;i++){
        for(int j = 0; j < Y; j++)
            std::cout << matrix[i][j].getLandscape()->getType() << " ";
        std::cout << std::endl;
    }
    printf("------------------\n");
}

void Field::printNeutrals() const {
    printf("-----Neutrals-----\n");
    if(matrix == nullptr)
    {
        printf("------------------\n");
        return;
    }
    for(int i = 0; i < X;i++){
        for(int j = 0; j < Y; j++)
            std::cout << matrix[i][j].getNeutral()->getType() << " ";
        std::cout << std::endl;
    }
    printf("------------------\n");
}

void Field::attack(int x, int y, int attackPower) {
    if(matrix[x][y].getCharacter())
    {
        matrix[x][y].getCharacter()->getDamage(attackPower);
        adapter->attack(matrix[x][y].getCharacter(), attackPower);
    }
    if(matrix[x][y].base)
        matrix[x][y].base->getDamage(attackPower);
}

void Field::deleteBase(Base* ptr)
{
    for(FieldIterator iter(this); iter != nullptr; iter++ )
    {
        if((*iter)->base == ptr)
        {
            delete (*iter)->base;
            (*iter)->base = nullptr;
            break;
        }
    }
}

Unit* Field::findUnit(std::string unitName)
{
    Unit* unit = nullptr;
    for(FieldIterator iter(this); iter != nullptr; iter++)
        if((*iter)->getCharacter() && (*iter)->getCharacter()->getName() == unitName)
        {
            unit = (*iter)->getCharacter();
            break;
        }
    return unit;
}

bool Field::findUnit(Unit* unit)
{
    for(FieldIterator iter(this); iter != nullptr; iter++)
        if((*iter)->getCharacter() && (*iter)->getCharacter()== unit)
        {
            return true;
        }
    return false;
}

Base* Field::findBase(int baseNumber) {
    Base *base = nullptr;
    for (FieldIterator iter(this); iter != nullptr; iter++)
        if ((*iter)->base && (*iter)->base->getNumber() == baseNumber) {
            base = (*iter)->base;
            break;
        }
    return base;
}

SnapShot* Field::makeSnapShot(std::string mode)
{
    SnapShot* tmp;
    if(mode == "save")
    {
        tmp = new SnapShot(this, base1, base2, base3, unit1, unit2, unit3, adapter, gameMode);
    }
    if(mode == "load")
    {
        tmp = new SnapShot(this);
    }
    return tmp;
}

///////////////////////////////////////////////////////////////////////


FieldIterator::FieldIterator(Field* ptr): fieldPtr(ptr),
tmpCell(ptr != nullptr ? ptr->matrix[0]: nullptr),
x(0),
y(0){ }

bool FieldIterator::operator==(const FieldIterator &other) const { return other.tmpCell == this->tmpCell;}

bool FieldIterator::operator!=(const FieldIterator &other) const { return other.tmpCell != this->tmpCell;}

Cell*& FieldIterator::operator++(int) {
    if(fieldPtr == nullptr)
    {
        tmpCell = nullptr;
        return tmpCell;
    }

    if(x == fieldPtr->getX())
    {
        x = 0;
        y++;
    }
    if(y == fieldPtr->getY())
    {
        tmpCell = nullptr;
        return tmpCell;
    }
    tmpCell = fieldPtr->matrix[x] + y;
    x++;
    return tmpCell;
}

Cell*& FieldIterator::operator*() {
    return tmpCell;
}

