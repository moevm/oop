#include "Trapeze.h"
#include <string>
Trapeze::Trapeze(std::string color, double angleA, double angleB, double a, double h) :Shape(color) {
	if (fmin(a, h)<0) throw "Trapeze init error: negative a or b\n";
	pts.push_back(Point(0, 0));
	pts.push_back(Point(a, 0));
	pts.push_back(Point(a - (h / tan(angleB)), h));
	pts.push_back(Point(h / tan(angleA), h));
	onTransformed();
}
void Trapeze::applyForAnyPoint(std::function<void(Point&)> const & f) {
	for (Point& p : pts)
		f(p);
};

std::string Trapeze::toString() const {
	return std::string("Shape = Trapeze\n")
		+ "id = " + std::to_string(getId()) + "\ncolor = " + getColor().def + "\n" + "vertexes:\n"
		+ "\t" + std::to_string(pts[0].x) + " " + std::to_string(pts[0].y) + "\n" +
		+"\t" + std::to_string(pts[1].x) + " " + std::to_string(pts[1].y) + "\n" +
		+"\t" + std::to_string(pts[2].x) + " " + std::to_string(pts[2].y) + "\n" +
		+"\t" + std::to_string(pts[3].x) + " " + std::to_string(pts[3].y) + "\n";
}
Trapeze::Trapeze(std::string color) :Shape(color) {}

double Trapeze::getA() {
	return a;
}

double Trapeze::getB() {
	return b;
}

void Trapeze::onTransformed() {
	a = length(pts[0], pts[1]);
	b = length(pts[2], pts[3]);
}