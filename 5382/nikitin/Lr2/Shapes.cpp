// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

void rotatex(double &coord, const double tempx, const double centerx, const double radangle, const double tempy, const double centery){
	coord = centerx + (tempx - centerx)*cos(radangle) - (tempy - centery)*sin(radangle);
}

void rotatey(double &coord, const double tempx, const double centerx, const double radangle, const double tempy, const double centery){
	coord = centery + (tempx - centerx)*sin(radangle) + (tempy - centery)*cos(radangle);
}

void lineqquation(double x1, double x2, double y1, double y2, double &k, double &b){
	k = (y2 - y1) / (x2 - x1);
	b = y2 - x1*k;
}

void intersectionpoint(double k1, double k2, double b1, double b2, double &x, double &y){
	x = (b2 - b1) / (k1 - k2);
	y = k1*x + b1;
}

bool compare(double x11, double x12, double y11, double y12, double x21, double x22, double y21, double y22, double x23, double x24, double y23, double y24){
	double k1 = 0, b1 = 0, k2 = 0, b2 = 0, x = 0, y = 0;
	lineqquation(x11, x12, y11, y12, k1, b1); // 1 сторона
	lineqquation(x21, x22, y11, y22, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 1
	lineqquation(x22, x23, y22, y23, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 2
	lineqquation(x23, x24, y23, y24, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 3
	lineqquation(x24, x21, y24, y21, k2, b2);
	intersectionpoint(k1, k2, b1, b2, x, y);
	if (((x > x11) && (x<x12)) || ((x>x12) && (x<x11))) return true; // c 4
	return false;
}

class Shape{
protected:
	double centerx, centery; // координаты центра
	string color; // цвет 
	int type;
public:
	double ltx, lty, ldx, ldy, rdx, rdy, rtx, rty; // координаты углов
	int angle; // угол на который повернута фигура
	Shape(double centerx, double centery, int angle, int type, string color = "white") : centerx(centerx), centery(centery), angle(angle), type(type), color(color) {}
	virtual ~Shape() {}
	virtual void move(double newcenterx, double newcentery) = 0;
	void rotate(int newangle){ // www.abakbot.ru/online-2/91-rotate
		double radangle = newangle * 3.14 / 180;
		double templtx = ltx; double templdx = ldx; double temprtx = rtx; double temprdx = rdx; double templty = lty; double templdy = ldy; double temprty = rty; double temprdy = rdy;
		rotatex(ltx, templtx, centerx, radangle, templty, centery);
		rotatey(lty, templtx, centerx, radangle, templty, centery);
		rotatex(rtx, temprtx, centerx, radangle, temprty, centery);
		rotatey(rty, temprtx, centerx, radangle, temprty, centery);
		rotatex(ldx, templdx, centerx, radangle, templdy, centery);
		rotatey(ldy, templdx, centerx, radangle, templdy, centery);
		rotatex(rdx, temprdx, centerx, radangle, temprdy, centery);
		rotatey(rdy, temprdx, centerx, radangle, temprdy, centery);
		angle = (angle + newangle) % 360;
	};
	virtual void scale(int n) = 0;
	void setcolor(string newcolor) { // устанавливает новый цвет фигуры
		color = newcolor;
	}
	string getcolor() const { // возвращает текущий цвет фигуры
		return color;
	}

	virtual bool check(Shape& shape1, Shape& shape2) = 0;

	friend ostream& operator <<(ostream& os, const Shape& shape){ // оператор вывода
		os << endl << "Current shape is ";
		if (shape.type == 1)cout << "Rectangle" << endl;
		if (shape.type == 2)cout << "Square" << endl;
		if (shape.type == 3)cout << "Ellipse" << endl;
		os << endl << "Current coords: " << "(" << shape.ltx << ";" << shape.lty << ")	(" << shape.ldx << ";" << shape.ldy << ")	(" << shape.rdx << ";" << shape.rdy << ")	(" << shape.rtx << ";" << shape.rty << ")" << endl;
		os << endl << "Current angle: " << shape.angle << endl;
		string temp = shape.getcolor();
		os << endl << "Current color: " << temp << endl << endl;
		return os;
	}
};


class Rectangle : public Shape{ // класс - пр€моугольник
protected:
	double width, height; // начальна€ ширина и высота пр€моугольника
public:
	Rectangle(double width, double height, double centerx, double centery, int angle = 0, int type = 1, string color = "white") : Shape(centerx, centery, angle, type, color), width(width), height(height){ // пр€моугольник задаетс€ через центр, высоту и ширину, потом высчитываютс€ координаты углов
		ldx = ltx = centerx - width / 2; rdx = rtx = centerx + width / 2;
		lty = rty = centery + height / 2; ldy = rdy = centery - height / 2;
	}
	void move(double newcenterx, double newcentery){ // смещаетс€ центр, далее высчитываютс€ углы
		centerx = newcenterx; centery = newcentery;
		ldx = ltx = centerx - width / 2; rdx = rtx = centerx + width / 2;
		lty = rty = centery + height / 2; ldy = rdy = centery - height / 2;
	}
	void scale(int n){ // увеличиваютс€ стороны, далее высчитываютс€ углы
		width *= n; height *= n;
		ldx = ltx = centerx - width / 2; rdx = rtx = centerx + width / 2;
		lty = rty = centery + height / 2; ldy = rdy = centery - height / 2;
	}

	bool check(Shape& shape1, Shape& shape2){
		bool answer = false;
		if (shape1.angle == 0){
			int angle = 360;
			shape1.rotate(angle);
		}
		if (shape2.angle == 0){
			int angle = 360;
			shape2.rotate(angle);
		}
		answer = compare(shape1.ltx, shape1.ldx, shape1.lty, shape1.ldy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.ldx, shape1.rdx, shape1.ldy, shape1.rdy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rdx, shape1.rtx, shape1.rdy, shape1.rty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rtx, shape1.ltx, shape1.rty, shape1.lty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		return answer;
	}
};

class Square : public Shape{ // класс - квадрат
protected:
	double side; // размер стороны
public:
	Square(double side, double centerx, double centery, int angle = 0, int type = 2, string color = "white") : Shape(centerx, centery, angle, type, color), side(side) {// квадрат задаетс€ через центр и сторону, потом высчитываютс€ координаты углов
		ldx = ltx = centerx - side / 2; rdx = rtx = centerx + side / 2;
		lty = rty = centery + side / 2; ldy = rdy = centery - side / 2;
	}
	void move(double newcenterx, double newcentery){ //аналогично с пр€моугольником
		centerx = newcenterx; centery = newcentery;
		ldx = ltx = centerx - side / 2; rdx = rtx = centerx + side / 2;
		lty = rty = centery + side / 2; ldy = rdy = centery - side / 2;
	}
	void scale(int n){ //аналогично с пр€моугольником
		side *= n;
		ldx = ltx = centerx - side / 2; rdx = rtx = centerx + side / 2;
		lty = rty = centery + side / 2; ldy = rdy = centery - side / 2;
	}
	bool check(Shape& shape1, Shape& shape2){
		bool answer = false;
		if (shape1.angle == 0){
			int angle = 360;
			shape1.rotate(angle);
		}
		if (shape2.angle == 0){
			int angle = 360;
			shape2.rotate(angle);
		}
		answer = compare(shape1.ltx, shape1.ldx, shape1.lty, shape1.ldy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.ldx, shape1.rdx, shape1.ldy, shape1.rdy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rdx, shape1.rtx, shape1.rdy, shape1.rty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rtx, shape1.ltx, shape1.rty, shape1.lty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		return answer;
	}

};

class Ellipse : public Shape{ //класс - эллипс
protected:
	double wradius, hradius;
public:
	Ellipse(double wradius, double hradius, double centerx, double centery, int angle = 0, int type = 3, string color = "white") : Shape(centerx, centery, angle, type, color), wradius(wradius), hradius(hradius){// эллипс задаетс€ через два радиуса: "ширины" и "высоты", потом высчитываютс€ координаты крайних точен этих радиусов (эллипс мысленно поворачиваетс€ ~45 град влево)
		ltx = rdx = centerx; rtx = centerx + wradius; ldx = centerx - wradius;
		ldy = rty = centery; lty = centery + hradius; rdy = centery - hradius;
	}
	void move(double newcenterx, double newcentery){//аналогично с пр€моугольником
		centerx = newcenterx; centery = newcentery;
		ltx = rdx = centerx; rtx = centerx + wradius; ldx = centerx - wradius;
		ldy = rty = centery; lty = centery + hradius; rdy = centery - hradius;
	}
	void scale(int n){ //аналогично с пр€моугольником
		wradius *= n; hradius *= n;
		rtx = centerx + wradius; ldx = centerx - wradius;
		lty = centery + hradius; rdy = centery - hradius;
	}
	bool check(Shape& shape1, Shape& shape2){
		bool answer = false;
		if (shape1.angle == 0){
			int angle = 360;
			shape1.rotate(angle);
		}
		if (shape2.angle == 0){
			int angle = 360;
			shape2.rotate(angle);
		}
		answer = compare(shape1.ltx, shape1.ldx, shape1.lty, shape1.ldy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.ldx, shape1.rdx, shape1.ldy, shape1.rdy, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rdx, shape1.rtx, shape1.rdy, shape1.rty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		answer = compare(shape1.rtx, shape1.ltx, shape1.rty, shape1.lty, shape2.ltx, shape2.ldx, shape2.lty, shape2.ldy, shape2.rdx, shape2.rtx, shape2.rdy, shape2.rty);
		if (answer) return answer;
		return answer;
	}
};

TEST(Intersection_Tests, Rectangle_and_Rectangle_True){
	Rectangle rec1(4, 2, 0, 0, 0);
	Rectangle rec2(4, 2, 1, 1, 0);
	EXPECT_EQ(true, rec1.check(rec1, rec2));
}
TEST(Intersection_Tests, Rectangle_and_Rectangle_False){
	Rectangle rec1(4, 2, 0, 0, 0);
	Rectangle rec2(4, 2, 4, 4, 0);
	EXPECT_EQ(false, rec1.check(rec1, rec2));
}
TEST(Intersection_Tests, Rectangle_and_Square_True){
	Rectangle rec1(4, 2, 0, 0, 0);
	Square sq1(2, 1, 1, 0);
	EXPECT_EQ(true, rec1.check(rec1, sq1));
}
TEST(Intersection_Tests, Rectangle_and_Square_False){
	Rectangle rec1(4, 2, 0, 0, 45);
	Square sq1(2, 3, 3, 45);
	EXPECT_EQ(false, rec1.check(rec1, sq1));
}
TEST(Intersection_Tests, Rectangle_and_Ellipse_True){
	Rectangle rec1(4, 2, 0, 0, 0);
	Ellipse ell1(4, 2, 1, 1, 0);
	EXPECT_EQ(true, rec1.check(rec1, ell1));
}
TEST(Intersection_Tests, Rectangle_and_Ellipse_False){
	Rectangle rec1(4, 2, -2,-22, 0);
	Ellipse ell1(2, 1, 3, 3, 0);
	EXPECT_EQ(false, rec1.check(rec1, ell1));
}
TEST(Intersection_Tests, Square_and_Square_True){
	Square sq1(2, 0, 0, 0);
	Square sq2(2, 1, 1, 0);
	EXPECT_EQ(true, sq1.check(sq1, sq2));
}
TEST(Intersection_Tests, Square_and_Square_False){
	Square sq1(2, 0, 0, 45);
	Square sq2(2, 3, 3, 45);
	EXPECT_EQ(false, sq1.check(sq1, sq2));
}
TEST(Intersection_Tests, Square_and_Ellipse_True){
	Square sq1(2, 0, 0, 0);
	Ellipse ell1(4,2, 2, 0, 0);
	EXPECT_EQ(true, sq1.check(sq1, ell1));
}
TEST(Intersection_Tests, Square_and_Ellipse_False){
	Square sq1(2, 0, 0, 45);
	Ellipse ell1(4, 2, 3, 3, 45);
	EXPECT_EQ(false, sq1.check(sq1, ell1));
}
TEST(Intersection_Tests, Ellipse_and_Ellipse_True){
	Ellipse ell1(4, 2, 0, 0, 0);
	Ellipse ell2(4, 2, 0, 0, 90);
	EXPECT_EQ(true, ell1.check(ell1, ell2));
}
TEST(Intersection_Tests, Ellipse_and_Ellipse_False){
	Ellipse ell1(4, 2, 0, 0, 0);
	Ellipse ell2(4, 2, 0, 3, 0);
	EXPECT_EQ(true, ell1.check(ell1, ell2));
}

GTEST_API_ int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(0, "Rus");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	return 0;
}

