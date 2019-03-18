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
	// CREATE 4 DIFFERENT SHAPES
	Shape *shapes[4];
	shapes[0] = new Sqare;
	shapes[1] = new Sqare(Point(10, 10), Point(11, 11));
	shapes[2] = new FivePointedStar(Point(0, 0), Point(0, 10));
	shapes[3] = new Pentagon(Point(1, 0), Point(0, 1));

	// TEST THEM ALL
	for (int i = 0; i < 4; i++){
		cout << "Sourse: " << endl;
		cout << *shapes[i];

		shapes[i]->scale(2.0);
		cout << "Scale(2.0): " << endl;
		cout << *shapes[i];

		shapes[i]->move(Point(0, 0));
		cout << "Move(0, 0): " << endl;
		cout << *shapes[i];

		shapes[i]->rotate(Point(10, 10), M_PI / 2);
		cout << "Rotate((10, 10), PI / 2)" << endl;
		cout << *shapes[i];
	}
	
	return 0;
}