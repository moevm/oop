#include <iostream>
#include <cstdlib>
#include "Shape.h"
#include "Square.h"
#include "Isosceles_triangle.h"
#include "Right_triangle.h"

using namespace std;

int main(){
	cout << "--------------------Square--------------------\n";
	Shape *ptr1 = new Square(1,2,3);
	Shape *ptr2 = new Square(50, -5, 5, "Grey");
	cout << *ptr1 << *ptr2;
	ptr1->movement(-30, 0);
	ptr1->scaling(3);
	ptr2->rotation(370);
	ptr2->setColour("Orange");
	cout << *ptr1 << *ptr2;
	
	cout << "----------------Right triangle----------------\n";
	Shape *ptr3 = new Right_triangle(25,2.5,7.5, 15);
	Shape *ptr4 = new Right_triangle(10, 4.75, 0.2, 1, "Red");
	cout << *ptr3 << *ptr4;
	ptr3->movement(12, -60);
	ptr3->setColour("Yellow");
	ptr4->rotation(-70);
	ptr4->scaling(4);
	cout << *ptr3 << *ptr4;
	
	cout << "--------------Isosceles triangle--------------\n";
	Shape *ptr5 = new Isosceles_triangle(23,13,32, 60);
	Shape *ptr6 = new Isosceles_triangle(15, -7.8, 25, -370, "Black");
	cout << *ptr5 << *ptr6;
	ptr5->movement(0, 0);
	ptr5->setColour("Green");
	ptr6->rotation(730);
	ptr6->scaling(0.5);
	cout << *ptr5 << *ptr6;
	
    return 0;
}