#ifndef LAB2_TRAPEZE_H
#define LAB2_TRAPEZE_H

#include <vector>
#include <cmath>
#include "Shape.h"

class Trapeze : public Shape {
public:
	// по смежным сторонам и углу
	Trapeze(std::string color, double angleA, double angleB, double a, double h);
	void applyForAnyPoint(std::function<void(Point&)> const & f) override;
	std::string toString() const override;
	double getA();
	double getB();

protected:
	void onTransformed() override;
	explicit Trapeze(std::string color);
	std::vector<Point> pts;
	double a; // сторона для трапеции и п-ма
private:
	double b; // для трапеции не видна
};
#endif //LAB2_TRAPEZE_H