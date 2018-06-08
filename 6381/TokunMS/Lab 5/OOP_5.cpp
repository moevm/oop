#include <iostream>
#include <cmath>
#include <ctime>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "OOP_Shapes.h"
using namespace std;

#define NumberOfShapes 10
#define ValueRange 50

void GenerateShapes(vector<shared_ptr<Shape> >& Shapes)
{
	srand(time(nullptr));
	for (shared_ptr<Shape> &shape : Shapes)
	{
		int object = rand() % 3;
		switch (object) 
		{
			case 0:
            {
				shape.reset(new Ellipse({ abs((float) (rand() % 20 + 1)),  abs((float) (rand() %20 + 1)) }, abs(rand() % ValueRange) + 1, abs(rand() % ValueRange) + 1));
				break;
			}
			case 1:
            {
				shape.reset(new Trapezium({ abs((float)(rand() % 20 + 1)),  abs((float)(rand() % 20 + 1)) }, { abs((float) (rand() % 20 + 1)),  abs((float) (rand() % 20 + 1)) }, abs((float)(rand() % ValueRange) + 1), abs((float)(rand() % ValueRange) + 1)));
				break;
			}
			case 2:
            {
				shape.reset(new IsoscelesTrapezium({ abs((float) (rand() % 20 + 1)),  abs((float) (rand() %20 + 1)) }, { abs((float) (rand() % 20 + 1)),  abs((float) (rand() %20 + 1)) }, abs((float)(rand() % ValueRange) + 1), abs((float)(rand() % ValueRange) + 1)));
				break;
			}
		}
	}
}

int main()
{
	vector<shared_ptr<Shape>> shapes(NumberOfShapes);
	GenerateShapes(shapes);
	
	cout << "Result of searching for elements:" << endl;
	for (shared_ptr<Shape> &shape : shapes) if (!(*shape).GetX() && !(*shape).GetY()) cout << *shape << endl;
	
	cout << "***********************************************" << endl;
	cout << "Deleted elements: " << endl;
	for(int i = 0, iterator = 0; i < NumberOfShapes; i++)
	{
		shared_ptr<Shape> &shape = shapes[i - iterator];
		if(!(*shape).GetX() && !(*shape).GetY())
		{
			shapes.erase(shapes.begin() + i - iterator);
			cout << "Deleted element number " << i+1 << endl;
			iterator++;
		}
	}
	cout << "***********************************************" << endl;
	cout << "Ramaining elements:" << endl;
	for (shared_ptr<Shape> &shape : shapes)	cout << *shape << endl;
	
	return 0;
}