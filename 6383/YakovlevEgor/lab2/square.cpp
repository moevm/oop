#include "square.h"
#include <string>

Square::Square(std::string color, double side) :Parallelogram(color) {
	if (side < 0)throw "Square init error: negative width or height\n";
	pts.push_back(Point(side / sqrt(2), 0));
	pts.push_back(Point(0, side / sqrt(2)));
	pts.push_back(Point(-side / sqrt(2), 0));
	pts.push_back(Point(0, -side / sqrt(2)));
	onTransformed();
}

std::string Square::toString() const {
	return std::string("Shape = Square\n")
		+ "id = " + std::to_string(getId()) + "\ncolor = " + getColor().def + "\n" + "vertexes:\n"
		+ "\t" + std::to_string(pts[0].x) + " " + std::to_string(pts[0].y) + "\n" +
		+"\t" + std::to_string(pts[1].x) + " " + std::to_string(pts[1].y) + "\n" +
		+"\t" + std::to_string(pts[2].x) + " " + std::to_string(pts[2].y) + "\n" +
		+"\t" + std::to_string(pts[3].x) + " " + std::to_string(pts[3].y) + "\n";
}