
#include "string"
#include "math.h"
#include <cmath>
#include <iostream>
#include <ostream>

enum ProjectionType { X = 0, Y = 1 };

struct Point
{
	double x, y;
};

struct my_color
{
	double r, g, b;
};


class Shape //áàçîâûé êëàññ
{
protected:
	Point center;	
	my_color color;
	int angle; // ïîâîðîò íà óãîë 

public:
	Shape() {} //êîíñòðóêòîð êëàññà
	virtual void move(Point newCenter) = 0;
	virtual void changesize(double k) = 0;
	virtual void turn(double angle)=0; // ïîâîðà÷èâàåò íà óãîë
	my_color getColor()	//ïîëó÷åíèå öâåòà
	{
		return this->color;
	}
	void setñolor(my_color color)	//óñòàíîâêà öâåòà
	{
		this->color = color;
	}
	virtual ostream &operator << (ostream &output)	//îïåðàòîð âûâîäà â ïîòîê
	{
		return output;
	}
	bool equalProjection(const Shape& other, const ProjectionType projection) const
	{
		double left1 = this->leftx();
		double left2 = other.leftx();
		if (left1 == left2) return true;
		else return false;
	}
	virtual double const leftx() const = 0;
};
class Ellips : public Shape //êëàññ îêðóæíîñòè
{
private:
	double R;
	double r;
	Point left;
public:
	Ellips(Point center, int _R = 1, int _r = 2);//êîíñòðóêòîð êëàññà
    void move(Point newCenter) ;
    void changesize(double k);
    void turn(double angle); // ïîâîðà÷èâàåò íà óãîë
	double const leftx() const;

	ostream &operator << (ostream &output)
	{
		my_color tmpColor = getColor();
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "Center-point {" << this->center.x << " ; " << this->center.y << "}" << endl;
		output << "R" << R << " r " << r << endl;
		return output;
	}
	virtual ~Ellips() {}
};


class SegEl : public Shape //êëàññ êâàäðàòà
{
private:
	Point left;
	Point right;
public:
	SegEl(Point center, Point left, Point right); //êîíñòðóêòîð êëàññà
	void move(Point newCenter);
	void changesize(double k);
	void turn(double angle); // âèðòóàëüíûé ìåòîä äëÿ ïîâîðà ôèãóðû íà óãîë
	double const leftx() const;
	ostream &operator << (ostream &output)
	{
		my_color tmpColor = getColor();
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " << endl;
		output << "Center-point {" << this->center.x << " ; " << this->center.y << "}" << endl;
		output << "Left-point {" << this->left.x << " ; " << this->left.y << "}" << endl;
		output << "Right-point {" << this->right.x << " ; " << this->right.y << "}" << endl;
		return output;
	}
	virtual ~SegEl() {}
};

class Parallelogramm : public Shape //êëàññ êâàäðàòà
{
private:
	double l,L;
public:
	Parallelogramm(Point center, int _l = 9, int _L = 3);
	void move(Point newCenter);
	void changesize(double k);
	void turn(double angle);  // âèðòóàëüíûé ìåòîä äëÿ ïîâîðà ôèãóðû íà óãîë
	double const leftx() const;
	ofstream &operator << (ofstream &output)
	{
		my_color tmpColor = getColor();
		output << "Color: " << "red component = " << tmpColor.r << ", green component = " << tmpColor.g << ", blue component = " << tmpColor.b << " " ;
		output << "First-point {" << this->center.x << " ; " << this->center.y << "}" << endl;
		output << "L " << L << "l"<<l << endl;
		return output;
	}
	virtual ~Parallelogramm() {}
};
