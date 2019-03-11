#include <iostream>
#include <cmath>
#include "point.h"
#include "shape.h"
#include "sqare.h"
#include "five_pointed_star.h"
#include "pentagon.h"

using namespace std;

int main()
{


	// TEST SQARE

	Sqare sq(Point(1, 0), Point(0, 1));

	cout << "Sourse sqare: " << endl;
	cout << sq;

	sq.scale(2.0);
	cout << "Scale(2.0): " << endl;
	cout << sq;

	sq.move(Point(10, 10));
	cout << "Move(10, 10): " << endl;
	cout << sq;

	sq.rotate(Point(0, 0), M_PI / 2);
	cout << "Rotate((10, 10), PI / 2)" << endl;
	cout << sq;

	Sqare sq0(Point(1.0, 0.0), Point(0.0, 1.0));
	cout << "Another sqare: " << endl;
	cout << sq0;
	// END TEST SQARE

	// TEST FIVE POINTED STAR
	FivePointedStar fps(Point(1.0, 0.0), Point(0.0, 1.0));
	cout << "Five pointed star: " << endl;
	cout << fps;
	// END TEST FIVE POINTED STAR
	// TEST PENTAGON
	Pentagon pnt(Point(1.0, 0.0), Point(0.0, 1.0));
	cout << "Pentagon: " << endl;
	cout << pnt;

	// END TEST PENTAGON

	
	return 0;
}