//
// Created by anton on 16.02.2020.
//

#include <iostream>
#include "Field.h"
Field::Field(int x, int y) :X(x), Y(y), matrix(new Cell*[X]), objectsCounter(0), maxObjectsOnField(x*y){
    for(int i = 0; i < X; i++) {
        matrix[i] = new Cell[Y];
        for(int j = 0; j < Y; j++)
            matrix[i][j].setCharacter(nullptr);
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

void Field::addObject(Unit *Object, int x, int y) {
    if(!Object->isOnField())
        Object->replace(this);
    if(checkPoint(x,y) && !matrix[x][y].getCharacter() &&  objectsCounter < maxObjectsOnField) {
        matrix[x][y].setCharacter(Object);
        Object->setX(x);
        Object->setY(y);
        objectsCounter++;
    }
}

int Field::getObjectCounter() const{
    return objectsCounter;
}

void Field::deleteObject(Unit *Object) {
    int requiredX = Object->getX();
    int requiredY = Object->getY();
    if(checkPoint(requiredX, requiredY) && matrix[requiredX][requiredY].getCharacter() == Object) {
        matrix[requiredX][requiredY].clearCell();
    }
    objectsCounter--;
}

void Field::print() const{
    printf("------------------\n");
    for(int i = 0; i < X;i++){
        for(int j = 0; j < Y; j++)
            if(matrix[i][j].getCharacter() != nullptr)
                std::cout << matrix[i][j].getCharacter()->getClass() << " ";
            else
                std::cout << ". ";
        std::cout << std::endl;
    }
    printf("------------------\n");
}

bool Field::checkPoint(int x, int y) const {
    return x < X && y < Y;
}

void Field::swapCharacters(int x1, int y1, int x2, int y2) {
    if(x1 == x2 && y1 == y2)
        return;
    //std::swap(matrix[x1][y1].Object, matrix[x2][y2].Object);
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

Field::Field(Field&& obj):X(0), Y(0), matrix(nullptr){
    std::swap(matrix, obj.matrix);
    std::swap(X, obj.X);
    std::swap(Y, obj.Y);
    std::swap(objectsCounter, obj.objectsCounter);
    std::swap(maxObjectsOnField, obj.maxObjectsOnField);
}

Field& Field::operator=(const Field& obj) {
    if(this == &obj)
        return *this;
    this->matrix = new Cell*[obj.X];
    this->X = obj.X;
    this->Y = obj.Y;
    this->objectsCounter = obj.objectsCounter;
    this->maxObjectsOnField = obj.maxObjectsOnField;
    for(int i = 0; i < X; i++) {
        this->matrix[i] = new Cell[Y];
        for (int j = 0; j < Y; j++) {
            this->matrix[i][j] = obj.matrix[i][j];
        }
    }
    return *this;
}

Field& Field::operator=(Field &&obj) {
    if(this == &obj)
        return *this;
    std::swap(matrix, obj.matrix);
    std::swap(X, obj.X);
    std::swap(Y, obj.Y);
    std::swap(objectsCounter, obj.objectsCounter);
    std::swap(maxObjectsOnField, obj.maxObjectsOnField);
    return *this;
}
