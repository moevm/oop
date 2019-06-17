
#include "pch.h""
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
	double x;
	double y;

	Point(double x, double y) :x(x), y(y) {}
};

struct Color {
	unsigned char r, g, b;

	Color(char r, char g, char b) :r(r), g(g), b(b) {}

};

class Shape {
protected:
	Point center;
	int angle;
	Color color;
public:
	Shape(const int angle = 0, const Point center = Point(0, 0), const Color color = Color(0, 0, 0)) :angle(angle), center(center), color(color) { }
	~Shape() {}

	Color get_color() { return color; }
	void change_color(Color color) {
		this->color = color;
	}

	virtual void scale(const double factor) = 0;

	void move(const Point new_center) {
		this->center = new_center;
	}

	void rotate(const int delta) {
		this->angle += delta;

		if (this->angle > 360)
			this->angle %= 360;
		if (this->angle < 0)
			this->angle += 360;
	}
};


class Square : public Shape {
//protected:
private:
	double a;
public:
	Square(const double a, const int angle = 0, const Point center = Point(0, 0), const Color color = Color(0, 0, 0))
		: Shape(angle, center, color), a(a) {}
	~Square() {}

	void scale(const double factor) override {
		if (factor <= 0) {
			return;
		}
		a *= factor;
	}

	friend std::ostream & operator << (std::ostream &out, const Square &obj) {
		out << "Square" << endl
			<< "Color = (" << int(obj.color.r) << ", " << int(obj.color.g) << ", " << int(obj.color.b) << ")" << endl
			<< "Center = (" << obj.center.x << ", " << obj.center.y << ")" << endl
			<< "Angle = " << obj.angle << endl
			<< "Edge of the square = " << obj.a << endl
			<< "______________" << endl;
			return out;
	}
};

class Pentagon : public Shape {
protected:
	double outer_radius;
public:
	Pentagon(const double outer_radius, const int angle = 0, const Point center = Point(0, 0), const Color color = Color(0, 0, 0))
		: Shape(angle, center, color), outer_radius(outer_radius) {}
	~Pentagon() {}

	void scale(const double factor) override {
		if (factor <= 0) {
			return;
		}
		outer_radius *= factor;
	}

	friend std::ostream & operator << (std::ostream &out, const Pentagon &obj) {
		out << "Pentagon" << endl
			<< "Color = (" << int(obj.color.r) << ", " << int(obj.color.g) << ", " << int(obj.color.b) << ")" << endl
			<< "Center = (" << obj.center.x << ", " << obj.center.y << ")" << endl
			<< "Angle = " << obj.angle << endl
			<< "Radius of the pentagon = " << obj.outer_radius << endl
			<< "____________" << endl;
			return out;
	}
};

class Fivepointed_star : public Pentagon {
protected:
	double internal_radius;
public:
	Fivepointed_star(const double internal_radius, const double outer_radius, const int angle, const Point center = Point(0, 0), const Color color = Color(0, 0, 0))
		: Pentagon(outer_radius, angle, center, color), internal_radius(internal_radius) {}
	~Fivepointed_star() {}

	void scale(const double factor) override {
		if (factor <= 0)
			return;
		internal_radius *= factor;
		outer_radius *= factor;
	}

	friend std::ostream & operator << (std::ostream &out, const Fivepointed_star &obj) {
		out << "A star" << endl
			<< "Color = (" << int(obj.color.r) << ", " << int(obj.color.g) << ", " << int(obj.color.b) << ")" << endl
			<< "Center = (" << obj.center.x << ", " << obj.center.y << ")" << endl
			<< "Angle = " << obj.angle << endl
			<< "Internal radius of the star = " << obj.internal_radius << endl
			<< "Outer radius of the star = " << obj.outer_radius << endl
			<< "______________" << endl;
			return out;
	}
};

int main()
{
	cout << "Square: " << endl;
	Square t(10);
	cout << t;
	cout << "Move Square to (30,20)..." << endl;
	t.move(Point(30, 20));
	cout << "Scale edges by 4..." << endl;
	t.scale(4);
	cout << "Rotate Square by 30dgr.." << endl;
	t.rotate(30);
	cout << "Change Square's color to (254,0,100)" << endl;
	t.change_color(Color(254, 0, 100));
	cout << t;

	Pentagon pent(40, 0, Point(100, 20), t.get_color());
	cout << pent;
	cout << "Fivepointed Star: " << endl;
	Fivepointed_star fp_star(70, 44, 90, Point(50, 200), Color(255, 255, 255));
	cout << fp_star;
	return 0;
}

