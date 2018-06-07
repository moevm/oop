#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

#define PI 3.14159265358979323846264338279502884197169399375

using namespace std;

struct Point{
	double x;
	double y;
};

class Shape {
protected:

	string color;
	int angle;
	double square;

public:
	virtual void move(double x, double y) = 0;
	virtual void scale(double coef) = 0;
	virtual void turn(int anglein) = 0;
	//virtual ~Shape() {};
	//virtual Shape() {};
	//void sec_menu(){};
	void setColor(string a);
	string getColor();
	virtual double getArea() = 0;
	virtual void printOUT(ostream& out) = 0; 
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}
	virtual void info() = 0;
};

class Circle : public Shape {

	Point center;
	Point right;
	Point top;
	Point left;
	Point bottom;
	double radius = 0;
	double square = 0;

public:
	Circle(double a, double b, double r){
		center = {a, b};
		radius = r;
		right = {a + r, b};
		top = {a, b + r};
		left = {a - r, b};
		bottom = {a, b - r};
		color = "black";
		angle = 0;
		square = PI * radius * radius;
		cout << "circle created, square = " << square << endl;
	}
	//~Circle() = default;
	void printOUT(ostream& out);
	void info();
	double getArea();
	void move(double x, double y);
	void turn(int anglein);
	void scale(double coeff);
};

class Rectangle: public Shape{

	Point center;
	Point rightT;
	Point rightB;
	Point leftT;
	Point leftB;
	double halfA;
	double halfB;
	double dia;
	double corner;
	double square;

public:
	Rectangle(double a, double b){
		center 	= {0	, 0};
		rightT 	= {a/2 	, b/2};
		rightB 	= {a/2	, -b/2};
		leftT 	= {-a/2	, b/2};
		leftB 	= {-a/2	, -b/2};
		color = "black";
		angle = 0;
		halfA = a/2;
		halfB = b/2;
		dia = sqrt(pow(halfA,2)+pow(halfB,2));
		corner = atan(((b/2)/(a/2)));//*180/PI);
		//cout << corner << endl;
		corner = corner / PI;
		//cout << corner << endl;
		corner = corner * 180;
		square = a * b;
		cout << "Rectangle created, square = " << square << endl;
		// cout << dia << endl;
		// cout << halfA << endl;
		// cout << halfB << endl;
		// cout << angle << endl;
		// cout << corner << endl;
		//cout << corner << endl;

	}
	//~Rectangle() = default;
	void move(double x, double y);
	void info();
	double getArea();
	void turn(int anglein);
	void scale(double coeff);
	void printOUT(ostream& out);
};

class Trapeze: public Shape{
	Point center;
	Point rightT;
	Point rightB;
	Point leftT;
	Point leftB;
	double dif1;
	double dif2;
	double height;
	double lenght;
	double dia;// = sqrt(pow(halfA,2)+pow(halfB,2));
	double corner;// = atan(((b/2)/(a/2)));//*180/PI);
	double square;
	
public:
	Trapeze(double a, double b, double h, int ang){
		center = {0 , 0};
		leftB = {-a/2 , -h/2};
		rightB = {a/2 , -h/2};
		if (ang == 90){
			leftT = {-a/2 , h/2};
			dif1 = 0;
		}
		else{
			leftT = {leftB.x + h/tan(ang*PI/180) , h/2};
			dif1 = h/tan(ang*PI/180);
		}
		rightT = {leftT.x + b , h/2};
		dif2 = a/2 - rightT.x;
		height = h;
		lenght = a;
		angle = 0;
		dia = sqrt(pow((lenght/2),2)+pow((height/2),2));
		corner = atan((b/2)/(a/2)) / PI * 180;
		color = "black";
		square = (a + b)/2 * h;
		cout << "Trapeze created, square = " << square << endl;
	};
	void info();
	double getArea();
	void move(double x, double y);
	void turn(int anglein);
	void scale(double coeff);
	void printOUT(ostream& out);
};

