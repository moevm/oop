//
// Created by anton on 16.02.2020.
//

#include <iostream>
#include "Field.h"
Field::Field(int x, int y) :X(x), Y(y), matrix(new Cell*[X]), objectsCounter(0), maxObjectsOnField(x*y){
    std::srand(time(nullptr));
    for(int i = 0; i < X; i++) {
        matrix[i] = new Cell[Y];
        for(int j = 0; j < Y; j++)
        {
            matrix[i][j].setCharacter(nullptr);
            matrix[i][j].setBase(nullptr);

            int value = rand()%3;
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

            value = rand()%4;
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
}

Field::Field():Field(0,0) {}

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

bool Field::addUnit(Unit *Object, int x, int y) {
    if(checkPoint(x,y) && !matrix[x][y].getCharacter() &&  objectsCounter < maxObjectsOnField && matrix[x][y].isAvailable(Object)) {
        matrix[x][y].setCharacter(Object);
        objectsCounter++;
        Object->setX(x);
        Object->setY(y);
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
            (*iter)->clearCell();
    objectsCounter--;
}

void Field::moveUnit(Unit *Object, int x, int y) {
    if(checkPoint(x,y) && matrix[x][y].isAvailable(Object))
    {
        puts("aa");
        deleteUnit(Object);
        matrix[x][y].landscape->impact(Object);
        matrix[x][y].neutral->getEffect(Object);
        addUnit(Object, x,y);
    }
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

void Field::swapCharacters(int x1, int y1, int x2, int y2) {
    if(x1 == x2 && y1 == y2)
        return;
    Unit* tmp = matrix[x1][y1].getCharacter();
    matrix[x1][y1].clearCell();
    matrix[x1][y1].setCharacter(matrix[x2][y2].getCharacter());
    matrix[x2][y2].clearCell();
    matrix[x2][y2].setCharacter(tmp);
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


Field::Field(const Field& obj) : Field(obj.X,obj.Y)
{
    objectsCounter = obj.objectsCounter;
    for(int i = 0; i < X; i++)
        for(int j = 0; j < Y; j++)
            this->matrix[X][Y] = obj.matrix[X][Y];
}

Field::Field(Field&& obj):X(obj.X), Y(obj.Y), matrix(nullptr), maxObjectsOnField(X*Y), objectsCounter(0) {
    std::swap(matrix, obj.matrix);
    std::swap(objectsCounter, obj.objectsCounter);
}

Base* Field::setBase( int x, int y, int maxObjects, int baseNumber) {
    Base* tmp = nullptr;
    if(checkPoint(x,y))
    {
        tmp = new Base(this, x, y, maxObjects, baseNumber);
        matrix[x][y].base = tmp;
        objectsCounter++;
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
        matrix[x][y].getCharacter()->getDamage(attackPower);
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

Unit* Field::findUnit(std::string& unitName)
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

Base* Field::findBase(int baseNumber) {
    Base *base = nullptr;
    for (FieldIterator iter(this); iter != nullptr; iter++)
        if ((*iter)->base && (*iter)->base->getNumber() == baseNumber) {
            base = (*iter)->base;
            break;
        }
    return base;
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
