// ConsoleApplication6.cpp: определяет точку входа для консольного приложения.
//

#include "shape.hpp"
#include "Triangle.hpp"
#include "Parallelogram.hpp"
#include "Rhombus.hpp"

#include "vector.hpp"
#include "sharedptr.hpp"

#define N 1000

using namespace std;

bool otl()
{};

void viborka()
{};


int main()
{
    srand(time(0));
    stepik::vector<stepik::shared_ptr<Shape>> vect(N);
    for (size_t i = 0; i < 1000; i++)
    {
        stepik::shared_ptr<Shape> shape;
        switch (rand() % 3)
        {
        case 0:
            shape = stepik::shared_ptr<Shape>(
                new Triangle(GetRandomPoint(), GetRandomPoint(), GetRandomPoint())
            );
            vect(N).push_back(stepik::shared_ptr<Shape>(shape));
            break;
        case 1:
            shape = stepik::shared_ptr<Shape>(
                Point a  = getRandomPoint();
                Point b  = getRandomPoint();
                Point c  = getRandomPoint();
                new Parallelogram(a, b, c, getFourthPoint(a, b, c))
            );
            vect(N).push_back(stepik::shared_ptr<Shape>(shape));
            break;
        case 2:
            shape = stepik::shared_ptr<Shape>(
                Point a  = getRandomPoint();
                Point b  = getRandomPoint();
                Point c  = getThirdPoint(a, b);
                new Rhombus(a, b, c, GetFourthPoint(a, b, c)));
            vect(N).push_back(stepik::shared_ptr<Shape>(shape));
            break;
        }
    }
    cout << otl(vect(N), 500) << endl;
    out(vect(N));
    system("PAUSE");
    return 0;
};
