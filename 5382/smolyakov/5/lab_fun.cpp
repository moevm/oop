#include "lab_fun.h"
#include <iostream>

Shape* generateShape() {
  switch (rand()%3) {
  case 0:
    return (new Triangle(RAND_IN_MAX,
                         Point(RAND_IN_MAX, RAND_IN_MAX),
                         Point(RAND_IN_MAX, RAND_IN_MAX)));
  case 1:
    return (new Rhombus(RAND_IN_MAX,
                        RAND_IN_MAX,
                        Point(RAND_IN_MAX, RAND_IN_MAX)));
  case 2:
    return (new Parallelogram(RAND_IN_MAX,
                              RAND_IN_MAX,
                              Point(RAND_IN_MAX, RAND_IN_MAX)));
  }
}

void generateShapes(shapeVec &vec, size_t n) {
  srand(time(NULL));
  for (size_t i = 0; i < n; i++) {
    vec.push_back(
                  stepik::shared_ptr<Shape*>
                  (new Shape*(generateShape())));
  }
}

void sortShapeVec(shapeVec &vec) {
  std::sort(vec.begin(), vec.end(),
            [](stepik::shared_ptr<Shape*> a,
               stepik::shared_ptr<Shape*> b) {
              return ((*a)->area()) < ((*b)->area());
            });
}

//Проверка разделен ли диапазон на две группы. Одна группа - фигуры внутри parametr, вторая иначе
bool alg1(const shapeVec& vec, const Shape& parametr) {
  unsigned short ind = 2;
  for (size_t i = 0; i < vec.size()-1; i++) {
    if (!ind)
      return 0;
    if (parametr.isInsideOfAnother(**(vec[i])) !=
        parametr.isInsideOfAnother(**(vec[i+1]))) {
      ind--;
    }
  }
  if (ind == 1)
    return 1;
  else
    return 0;
}

bool alg1(const shapeVec& vec) {
  return alg1(vec, (Parallelogram(10, 10, Point(-5, -5))));
}

// Создаёт отсортированное пересечение двух массивов
shapeVec alg2(shapeVec& vec1, shapeVec& vec2) {
  shapeVec res;
  sortShapeVec(vec1);
  sortShapeVec(vec2);
  std::set_intersection(vec1.begin(), vec1.end(),
                        vec2.begin(), vec2.end(),
                        std::back_inserter(res),
                        [](stepik::shared_ptr<Shape*> a,
                           stepik::shared_ptr<Shape*> b) {
                          return ((*a)->area()) < ((*b)->area());
                        });
  return res;
}   

