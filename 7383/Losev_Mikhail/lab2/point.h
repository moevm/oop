#pragma once


class Point
{
public:
	
	Point();
	Point(int x, int y);
	~Point();

	double get_x() const;
	double get_y() const;

	void set_x(double);
	void set_y(double);

	void rotate(Point cntr, double ang);
	void move(Point);

	Point operator+(Point& b);
	Point operator-(Point& b);

	//Point operator*(const double b);
	friend std::ostream& operator<<(std::ostream& out, const Point& obj);

private:
	
	double x;
	double y;
};