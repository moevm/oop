#include "vector.h"
#include "shared_ptr.cpp"
#include "figure.h"
#define MAX_VALUE 100
#define RAND_IN_MAX rand()%MAX_VALUE+1

using namespace stepik;

typedef stepik::vector<stepik::shared_ptr<Shape*>> shapeVec;

Shape* generateShape();

void generateShapes(shapeVec &vec, size_t n = 1000);

void sortShapeVec(shapeVec &vec); 

//Проверка разделен ли диапазон на две группы. Одна группа - фигуры внутри parametr, вторая иначе
bool alg1(const shapeVec& vec, const Shape& parametr);

bool alg1(const shapeVec& vec);

// Создаёт отсортированное пересечение двух массивов
shapeVec alg2(shapeVec& vec1, shapeVec& vec2);

