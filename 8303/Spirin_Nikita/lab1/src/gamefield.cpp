#include "gamefield.h"


GameField::GameField(int height, int width) : height(height), width(width), maxNumOfObj(height * width)
{
    field = new Cell*[height];
    for(int i = 0; i < height; ++i){
        field[i] = new Cell[width];
    }
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++){
            field[i][j].value = '0';
            field[i][j].unit = nullptr;
        }
}

GameField::GameField(GameField const& f) : height(f.height), width(f.width), numOfObj(f.numOfObj), maxNumOfObj(f.maxNumOfObj)
{
    field = new Cell*[height];
    for(int i = 0; i < height; ++i){
        field[i] = new Cell[width];
    }
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++){
            field[i][j].value = f.field[i][j].value;
            field[i][j].unit = f.field[i][j].unit;
        }
}

GameField::GameField(GameField&& f) :  field(f.field), height(f.height), width(f.width), numOfObj(f.numOfObj), maxNumOfObj(f.maxNumOfObj)
{

    f.field = nullptr;
    f.numOfObj = 0;
}


void GameField::printField() const
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            std::cout << field[i][j].value;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GameField::addUnit(Unit* unit, int y, int x)
{
    //std::cout << unit->getID() << std::endl;
    if(unit->isPosted){
        qDebug() << "This unit is posted on the field!";
        return;
    }
    if(numOfObj + 1 >= maxNumOfObj){
        qDebug() << "It is impossible add a new object, the maximum number of objects per field!";
        return;
    }
    if(y >= height || y < 0 || x >= width || x < 0){
        qDebug() << "Inccorrect coordinates!";
        return;
    }
    if(field[y][x].unit != nullptr){
        qDebug() << "Place taken!";
        return;
    }
    unit->isPosted = true;
    field[y][x].value = unit->getID();
    field[y][x].unit = unit;
    unit->y = y;
    unit->x = x;
    numOfObj++;
}

void GameField::deleteUnit(Unit* unit)
{
    int y = unit->y;
    int x = unit->x;
    if(y >= height || y < 0 || x >= width || x < 0){
        qDebug() << "Inccorrect coordinates!";
        return;
    }
    if(field[y][x].unit == nullptr){
        qDebug() << "Place is free!";
        return;
    }
    unit->isPosted = false;
    field[y][x].value = '0';
    field[y][x].unit = nullptr;
    numOfObj--;
}

void GameField::moveUnit(Unit* unit, int y, int x)
{
    if(y >= height || y < 0 || x >= width || x < 0){
        qDebug() << "Inccorrect coordinates!";
        return;
    }
    if(field[y][x].unit != nullptr){
        qDebug() << "Place taken!";
        return;
    }
    if(unit->isPosted == false){
        qDebug() << "Unit is not standing on field!";
        return;
    }

    deleteUnit(unit);
    addUnit(unit, y, x);
}


//    point->y = y;
//    point->x = x;
//    arrOfPoints = new ArrOfPoints();
//    findWay(y0, x0, 1);
//    arrOfPoints->print();


//void GameField::findWay(int y, int x, int length)
//{
//    if(y == point->y && x == point->x)
//        return;
//    if(y + 1 < height){
//        PointOfWay* pointOfWay = new PointOfWay(y, x, length);
//        arrOfPoints->push(pointOfWay);
//        findWay(y + 1, x, length + 1);
//    }
//    if(y - 1 >= 0){
//        PointOfWay* pointOfWay = new PointOfWay(y, x, length);
//        arrOfPoints->push(pointOfWay);
//        findWay(y - 1, x, length + 1);
//    }
//    if(x + 1 < width){
//        PointOfWay* pointOfWay = new PointOfWay(y, x, length);
//        arrOfPoints->push(pointOfWay);
//        findWay(y, x + 1, length + 1);
//    }
//    if(x - 1 >= 0){
//        PointOfWay* pointOfWay = new PointOfWay(y, x, length);
//        arrOfPoints->push(pointOfWay);
//        findWay(y, x - 1, length + 1);
//    }
//}

