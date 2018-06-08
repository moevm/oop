#include <iostream>
#include <cmath>
#include <ctime>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

static vector<string> colors {"transparent", "red", "yellow", "blue", "white", "black"};

class Point
{
public:
	float x;
	float y;

	Point(float x_, float y_);
	void move(float x_, float y_);
	void rotate(float alpha);
	void scale(Point point0, float k);
};
 
class Shape
{
private:
	unsigned color;	
protected:
	vector<Point> point;
public:
	virtual ~Shape();
	virtual void Scale(float k) = 0;
	virtual ostream& put(ostream& out) const = 0;
	friend ostream& operator<< (ostream& s, const Shape& shape_);
	virtual float Perimeter() = 0;
	Shape();
    bool GetX();
    bool GetY();
	void Move(float x_, float y_);
	void Rotate(float alpha);
	void setColor(unsigned color_);
	unsigned getColor() const;
	
};

class Ellipse : public Shape
{
private:
	float r1;
	float r2;
public:
	Ellipse(Point center, float r1_, float r2_);
	void Scale(float k);
	float Perimeter(); 
	ostream& put(ostream& out) const;
	
};

class Trapezium : public Shape
{
private:	
	virtual string FriendlyName() const;
protected:
	float topBase;
	float bottomBase;
public:
	Trapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_);
	void Scale(float k);   
	float Distance(Point a, Point b);
	float Perimeter();
	ostream& put(ostream& out) const;
	
};

class IsoscelesTrapezium : public Shape
{
protected:
	float topBase;
	float bottomBase;
private:
	virtual string FriendlyName() const;
public:
	IsoscelesTrapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_);
    ostream& put(ostream& out) const;
    void Scale(float k);
    float Distance(Point a, Point b);
    float Perimeter();
};