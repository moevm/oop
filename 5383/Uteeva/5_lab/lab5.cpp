#include <iostream>
#include <algorithm>
#include "vector.h"
#include "Shared_ptr.h"
#include "Shape.h"
#include "round.h"
#include "RegPentagon.h"
#include "Pentagon.h"
#include <functional>

using namespace std;
using namespace stepik;

const float diapason = 15;

double random(double fMin = -diapason, double fMax = diapason)
 {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
	}

std::vector< shared_ptr<Shape>> generator() {
	std::vector<shared_ptr<Shape>> array1;
	for (size_t i = 0; i < 1000; ++i) {
	static size_t x;
		x = rand() % 3;
	
			switch (x) {
			
				case 0: {
				array1.push_back(shared_ptr<Shape>
					(new Round(random(0), Point(random(), random()), Color(random(), random(), random()))));
				break;
			}
			
				case 1: {
				array1.push_back(shared_ptr<Shape>
					(new Pentagon(Point(random(), random()), Point(random(), random()), Point(random(), random()), Point(random(), random()), Point(random(), random()), Color(random(), random(), random()))));
				break;
				}
			
				case 2: {
				array1.push_back(shared_ptr<Shape>
					(new RegPentagon(Point(random(), random()), Point(random(), random()), Color(random(), random(), random()))));
				break;
				}
			
		}
		
	}
	return array1;
	
}

bool predicate(const shared_ptr<Shape> &a, const shared_ptr<Shape> &b) {
	return b->isInsideOfAnother(*a);
}




int main() {
	
		setlocale(0, "Rus");

		Point *center = new Point(10, 10);
		Color *color = new Color(1, 0, 2);

		shared_ptr<Shape> shared_shape1(new Round(10, *center, *color));
		shared_ptr<Shape> shared_shape2(new Round(15, *center, *color));
	    shared_ptr<Shape> shared_shape3(new Round(13, *center, *color));
		shared_ptr<Shape> shared_shape4(new Round(11, *center, *color));
		shared_ptr<Shape> shared_shape5(new Round(12, *center, *color));

	//Поиск первого элемента удовлетворяющего определенному критерию (Немодифициующий алгоритм)

		std::vector<shared_ptr<Shape>> vec;
		vec.push_back(shared_ptr<Shape>(shared_shape1));
		vec.push_back(shared_ptr<Shape>(shared_shape2));
		vec.push_back(shared_ptr<Shape>(shared_shape3));
		vec.push_back(shared_ptr<Shape>(shared_shape4));
		vec.push_back(shared_ptr<Shape>(shared_shape5));


		std::cout << std::endl << "Unmodify Algorithm:" << std::endl;
		shared_ptr<Shape> find_1 = *(std::find_if(vec.begin(), vec.end(), predicate));



	//Заменить элементы, соответствующие критерию другим значением.
		std::cout << "Modify Algorithm" << std::endl;
		std::replace_if(vec.begin(), vec.end(), predicate, shared_shape1);


	system("pause");
	return 0;
	
}