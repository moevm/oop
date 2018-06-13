// ConsoleApplication6.cpp: определяет точку входа для консольного приложения.
//

#include "shape.hpp"
#include "Triangle.hpp"
#include "Parallelogram.hpp"
#include "Rhombus.hpp"

using namespace std;

void test1()
{
	Point a(1, 2);
	Point b(3, 4);
	Point c(5, 3);
	Triangle* triangle1 = new Triangle(a, b, c);
	triangle1->setColor(1000);
	triangle1->turnAround(1);
	triangle1->resize(2);
	triangle1->moveByDelta(5);
	a = triangle1->getPointA();
	b = triangle1->getPointB();
	c = triangle1->getPointC();
	Point center = triangle1->getCenter();
	cout << a << "\n" << b << "\n" << c << "\n" << center << "\n";
	triangle1->printColor();
	system("pause");
}

void test2()
{
	Point a(1, 2);
	Point b(3, 4);
	Point c(5, 3);
	Point d(7, 5);
	Parallelogram* paral1 = new Parallelogram(a,b,c,d);
	paral1->setColor(100000);
	if (!paral1->isParallelogram())
		cout << "Not a parallelogram" << "\n";
	paral1->turnAround(1);
	paral1->resize(2);
	paral1->moveByDelta(5);
	a = paral1->getPointA();
	b = paral1->getPointB();
	c = paral1->getPointC();
	Point center = paral1->getCenter();
	cout << a << "\n" << b << "\n" << c << "\n" << d << "\n" << center << "\n";
	paral1->printColor();
	system("pause");
}

void test3()
{
	Point a(1, 2);
	Point b(2, 6);
	Point c(5, 3);
	Point d(6, 7);
	Rhombus* romb1 = new Rhombus(a, b, c, d);
	romb1->setColor(10000000);
	if (!romb1->isRhombus())
		cout << "Not a rhombus" << "\n";
	romb1->turnAround(1);
	romb1->resize(2);
	romb1->moveByDelta(5);
	a = romb1->getPointA();
	b = romb1->getPointB();
	c = romb1->getPointC();
	Point center = romb1->getCenter();
	cout << a << "\n" << b << "\n" << c << "\n" << d << "\n" << center << "\n";
	romb1->printColor();
	system("pause");
}

int main()
{
	test1();
	test2();
	test3();
    return 0;
}

