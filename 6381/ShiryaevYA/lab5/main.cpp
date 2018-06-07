#include "shape.h"

int main(){
	srand(time(NULL));
	int n = 0;
	string color;
	vector <shared_ptr<Shape> > shapes;
	shared_ptr<Shape> ptr;
	for (size_t i = 0; i < 10; ++i){
		n = rand() % 3;
		if (n == 0) 
			shapes.push_back(shared_ptr<Shape>(new Circle(0, 0, 1)));
		else if (n == 1)
			shapes.push_back(shared_ptr<Shape>(new Trapeze(1, 2, 1, 30)));
		else 
			shapes.push_back(shared_ptr<Shape>(new Rectangle(1, 2)));
	}
	sort(shapes.begin(), shapes.end(), 
                [&](shared_ptr<Shape> const &lhs, shared_ptr<Shape> const &rhs)
                {
                    return lhs.get()->getArea() < rhs.get()->getArea();
                }
        );
	for (size_t i = 0; i < 10; ++i){
		shapes[i].get()->info();
	}
	cout << "enter color" << endl;
	cin >> color;
	for (size_t i = 0; i < 10; ++i){
		shapes[i].get()->setColor(color);
		shapes[i].get()->info();	
	}
	//cout << shapes[0].use_count() << endl;
	return 0;
}