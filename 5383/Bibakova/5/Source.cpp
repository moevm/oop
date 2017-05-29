#include <iostream>
#include <functional>

#include "vector.h"
#include "sharedptr.hpp"
#include "shape.hpp"
#include "Circle.hpp"
#include "Pentagon.hpp"
#include "RegularPentagon.hpp"

using namespace std;

void change(rabid::vector < rabid::shared_ptr< Shape > > sourcev,
	Shape &rep,
	std::function< bool(const Shape&)> pred)
{
	for (auto& i : sourcev)
	{
		if (pred(*i)) i.reset(&rep);
	};
	return;
};

rabid::shared_ptr< Shape > findShape(rabid::vector < rabid::shared_ptr< Shape > > sourcev,
	std::function< bool(const Shape&)> pred)
{
	for (auto& i : sourcev)
	{

		if (pred(*i)) return i;
	};
	throw exception("not found");
};

int main()
{
	const int SHAPECOUNT = 15;
	const double BORDER = 40;
	const double RBORDER = 10;


	srand(time(NULL));

	rabid::vector < rabid::shared_ptr< Shape > > ofShapes(SHAPECOUNT);

	for (auto& i : ofShapes)
	{
		int a = rand() % 3;
		int col = rand() % 9;
		switch (a)
		{
		case 0:
			i = (rabid::shared_ptr< Shape > )new Circle({ randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) }, randNumber(1, RBORDER), Shape::ofColours[col]);
			break;
		case 1:
			i = (rabid::shared_ptr< Shape >)new Pentagon({ randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) },
														 { randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) }, 
														 { randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) }, 
														 { randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) }, 
														 { randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) }, 
														 Shape::ofColours[col] );
			break;
		case 2:
			i = (rabid::shared_ptr< Shape >)new RegularPentagon({ randNumber(-BORDER, BORDER), randNumber(-BORDER, BORDER) }, randNumber(1, RBORDER), Shape::ofColours[col]);
			break;
		default:
			break;
		}
	};


	rabid::shared_ptr< Shape > ref = (rabid::shared_ptr< Shape >)new Circle( { 0, 0 }, 4, "red" );
	rabid::shared_ptr< Shape > bald = (rabid::shared_ptr< Shape >)new Circle({ 0, 0 }, 30, "RED");
	

	const auto lamda = [ref](const Shape& s) { return ref.get()->equalÎxProjectionLength(s); };

	Circle* circle = new Circle({ 0, 0 }, 30, "RED");
	change(ofShapes, *circle, lamda);

	/*rabid::shared_ptr< Shape > res = findShape(ofShapes, lamda);
	if (res) cout << *res;
	else cout << "NOT FOUND" << endl;*/



	for (auto& i : ofShapes)
	{
		cout << *i;
	}


	return 0;
};



