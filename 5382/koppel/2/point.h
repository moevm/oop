
#ifndef POINT_H
#define POINT_H

class Point {
public:

	double x;
	double y;
	Point();
	Point(double x, double y);
	bool distance(const Point &smth) const; //расстояние
	friend bool operator == (const Point& first, const Point& second) {
		return ((first.x == second.x) && (first.y == second.y));
	}
	
};

#endif 