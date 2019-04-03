#include "stdafx.h"
#include <iostream>
#include <string>

class Shape {
protected:
	unsigned int* color = new unsigned int(3);
	int* x_arr;
	int* y_arr;

	int count_of_points;
	int x, y;
	int angle;

	// initialization;
	char type;
	int number;

public:
	virtual void SetID(int n) = 0;
	std::string GetID() {
		std::string str;
		str += type;
		str += std::to_string(number);
		return str;
	}
	friend std::ostream& operator << (std::ostream& out, const Shape& c) {
		return out << "ID:" << c.type << c.number << std::endl;
	}

	void SetPoint(int x_, int y_) {
		x = x_;
		y = y_;
	}
	void SetAngle(int ang) {
		angle = ang;
	}
	void SetScale(float scale) {
		if (scale > 0.0)
			for (int i = 0; i < count_of_points; i++) {
				x_arr[i] = (int)(x_arr[i] * scale);
				y_arr[i] = (int)(y_arr[i] * scale);
			}
	}

	void SetColor(unsigned int r, unsigned int g, unsigned int b) {
		if (r > 255) r = 255;
		if (g > 255) g = 255;
		if (b > 255) b = 255;
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
	unsigned int* GetColor() { return color; }

	Shape() {
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		count_of_points = 0;
		angle = 0;
		x = 0;
		y = 0;
	}
	~Shape() { delete[] color; }
};

class Square : public Shape {
public:
	Square() {
		count_of_points = 4;
		x_arr = new int(4);
		y_arr = new int(4);
		x_arr[0] = 0;
		y_arr[0] = 1;
		x_arr[1] = 1;
		y_arr[1] = 1;
		x_arr[2] = 0;
		y_arr[2] = 0;
		x_arr[3] = 1;
		y_arr[3] = 0;
	}
	Square(int x_left_up, int y_left_up, int size) {
		count_of_points = 4;
		x_arr = new int(4);
		y_arr = new int(4);
		x_arr[0] = x_left_up;		// left_up;
		y_arr[0] = y_left_up;
		x_arr[1] = x_left_up + size;	// right_up;
		y_arr[1] = y_left_up;
		x_arr[2] = x_left_up;		// left_down;
		y_arr[2] = y_left_up - size;
		x_arr[3] = x_left_up + size;	// right_down;
		y_arr[3] = y_left_up - size;
	}
	void SetID(int n) {
		type = 's';
		number = n;
	}
	~Square() {
		delete[] x_arr;
		delete[] y_arr;
	}
	friend std::ostream& operator << (std::ostream& out, const Square& c) {
		return out << "ID:" << c.type << c.number << std::endl << "Points: (" <<
			c.x_arr[0] << ", " << c.y_arr[0] << "); (" << c.x_arr[1] << ", " << c.y_arr[1] << "); (" <<
			c.x_arr[2] << ", " << c.y_arr[2] << "); (" << c.x_arr[3] << ", " << c.y_arr[3] << ")" << std::endl;
	}
};

class Allipse : public Shape {
private:
	int a_range, b_range;
public:
	Allipse() : a_range(1), b_range(1) {
		count_of_points = 1;
		x_arr = new int(1);
		y_arr = new int(1);
		x_arr[0] = 0;
		y_arr[0] = 0;
	}
	Allipse(int x_, int y_, int a, int b) : a_range(a), b_range(b) {
		count_of_points = 1;
		x_arr = new int(1);
		y_arr = new int(1);
		x_arr[0] = x_;
		y_arr[0] = y_;
	}
	void SetID(int n) {
		type = 'a';
		number = n;
	}
	~Allipse() {
		delete[] x_arr;
		delete[] y_arr;
	}
	friend std::ostream& operator << (std::ostream& out, const Allipse& c) {
		return out << "ID:" << c.type << c.number << std::endl << "Center: (" << c.x_arr[0] << ", " << c.y_arr[0] <<
			"); HorizontalRadius: " << c.a_range << "; VerticalRadius: " << c.b_range << std::endl;
	}
};

class Rhombus : public Shape {
public:
	Rhombus() {
		count_of_points = 4;
		x_arr = new int(4);
		y_arr = new int(4);
		x_arr[0] = 0;
		y_arr[0] = 1;
		x_arr[1] = -1;
		y_arr[1] = 0;
		x_arr[2] = 1;
		y_arr[2] = 0;
		x_arr[3] = 0;
		y_arr[3] = -1;
	}
	Rhombus(int x_upper, int y_upper, int x_left, int y_left) {
		count_of_points = 4;
		x_arr = new int(4);
		y_arr = new int(4);
		x_arr[0] = x_upper;				// up;
		y_arr[0] = y_upper;
		x_arr[1] = x_left;				// left;
		y_arr[1] = y_left;
		x_arr[2] = x_left + 2 * (x_upper - x_left);	// right;
		y_arr[2] = y_left;
		x_arr[3] = x_upper;				// down;
		y_arr[3] = y_upper - 2 * (y_upper - y_left);
	}
	void SetID(int n) {
		type = 'r';
		number = n;
	}
	~Rhombus() {
		delete[] x_arr;
		delete[] y_arr;
	}
	friend std::ostream& operator << (std::ostream& out, const Rhombus& c) {
		return out << "ID:" << c.type << c.number << std::endl << "Points: (" <<
			c.x_arr[0] << ", " << c.y_arr[0] << "); (" << c.x_arr[1] << ", " << c.y_arr[1] << "); (" <<
			c.x_arr[2] << ", " << c.y_arr[2] << "); (" << c.x_arr[3] << ", " << c.y_arr[3] << ")" << std::endl;
	}
};

int main() {
	return 0;
}