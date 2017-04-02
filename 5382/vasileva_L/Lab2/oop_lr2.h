#ifndef OOP_LR2
#define OOP_LR2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

class Shape
{
protected:
	unsigned color;
	int id = 0;
	std::vector<float> x;
	std::vector<float> y;
public:
	Shape();
	virtual ~Shape() {};
	int getId();
	void Move(float x_, float y_);  
	void Rotate(float alpha);
	void setColor(unsigned color_);
	void getColor();
	virtual void Scale(float k) = 0;
	virtual std::ostream& put(std::ostream& out) const = 0;
	friend std::ostream& operator<< (std::ostream& s, const Shape& shape_);
};

class Ellipse : public Shape
{
private:
	float r1;
	float r2;
public:
	Ellipse(float xc, float yc, float r1_, float r2_);
	void Scale(float k);
	std::ostream& put(std::ostream& out) const;
};

class Trapezium : public Shape
{
protected:
	float topBase;
	float bottomBase;
	std::string outputIsolated; 
public:
	Trapezium(float topLeft_x, float topLeft_y, float bottomLeft_x, float bottomLeft_y, float topBase_, float bottomBase_);
	void Scale(float k);
	std::ostream& put(std::ostream& out) const;
};

class IsoscelesTrapezium : public Trapezium
{
public:
	IsoscelesTrapezium(float topLeft_x, float topLeft_y, float bottomLeft_x, float bottomLeft_y, float bottomBase);
};
#endif
