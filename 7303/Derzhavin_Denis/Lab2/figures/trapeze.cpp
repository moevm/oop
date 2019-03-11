#pragma once

#include "trapeze.h"

Trapeze::Trapeze(Line l1,Line l2, Color color): Shape(Point(0,0), color), b1(l1), b2(l2) {
	if ((l1.p1.x == l1.p2.x && l1.p2.x == l2.p1.x && l2.p1.x == l2.p2.x) ||
		(l1.p1.y == l1.p2.y && l1.p2.y == l2.p1.y && l2.p1.y == l2.p2.y))
	 		throw logic_error("Bad trapeze");

 	if (l1.getTan() != l2.getTan())
 		throw logic_error("Bad trapeze"); 

 	center = makeCenter();
}

Trapeze::Trapeze(Point p1, Point p2, Point p3, Point p4, Color color): Shape(Point(0,0), color) {
	Line l12 = Line(p1, p2), l34 = Line(p3, p4),
		 l13 = Line(p1, p3), l24 = Line(p2, p4),
		 l14 = Line(p1, p4), l23 = Line(p2, p3);

	if ((p1.x == p2.x && p2.x == p3.x && p3.x == p4.x) ||
 		(p1.y == p2.y && p2.y == p3.y && p3.y == p4.y))
 			throw logic_error("Bad trapeze");

 	if (l12.getTan() == l34.getTan()) {
 	 	b1 = l12;
 	 	b2 = l34;
 	} else if (l13.getTan() == l24.getTan()) {
 	 	b1 = l13;
 	 	b2 = l24;
 	} else if (l14.getTan() == l23.getTan()) {
 	 	b1 = l14;
 	 	b2 = l23;
 	} else 
 	 	throw logic_error("Bad trapeze");
	
	center = makeCenter();
}

Point Trapeze::makeCenter() {
	return Point((b1.p1.x + b1.p2.x + b2.p1.x + b2.p2.x)/4.0,
				 (b1.p1.y + b1.p2.y + b2.p1.y + b2.p2.y)/4.0);
}

void Trapeze::setPos(Point p) {
	fundament::moveTwoPoints(center, b1.p1, p);
	fundament::moveTwoPoints(center, b1.p2, p);
	fundament::moveTwoPoints(center, b2.p1, p);
	fundament::moveTwoPoints(center, b2.p2, p);
}

void Trapeze::scale(double k) {
	fundament::pullOutFromCenter(center, b1.p1, k);
	fundament::pullOutFromCenter(center, b1.p2, k);
	fundament::pullOutFromCenter(center, b2.p1, k);
	fundament::pullOutFromCenter(center, b2.p2, k);
}

void Trapeze::rotate(double angle) {
	fundament::rotate(center, b1.p1, angle);
	fundament::rotate(center, b1.p2, angle);
	fundament::rotate(center, b2.p1, angle);
	fundament::rotate(center, b2.p2, angle);
}

ostream& operator <<(ostream& stream, Trapeze& trapeze) {
	stream << dynamic_cast<Shape&>(trapeze) 
		   << "Длина меньшего основания: " << trapeze.getSmallBase().getLength() << endl
		   << "Длина большего основания: " << trapeze.getBigBase().getLength()   << endl;
}