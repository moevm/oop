#include "lab2.h"

Shape* generateRandomShape()
{
    int type = rand() % 4;

    switch (type)
    {
    case 0:
        return new Square(100);
    case 1:
        return new Rectangle(100);
    case 2:
        return new RightTriangle(100);
    case 3:
        return new IsoscelesTriangle(100);

    default:
        return nullptr;
    }
}

stepik::vector< stepik::shared_ptr<Shape> > generateShapes(size_t n)
{
    srand(time(NULL));
    stepik::vector< stepik::shared_ptr<Shape> > shapes(n);

    for (size_t i = 0; i < n; i++)
    {
        shapes[i] = stepik::shared_ptr<Shape>( generateRandomShape() );
    }

    return shapes;
}
