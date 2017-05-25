#pragma once
#include <iostream>
#include "Dot.h"
#include <vector>

struct Color {
	unsigned char R, G, B;
	Color(unsigned char _R = 0, unsigned char _G = 0, unsigned char _B = 0) : R(_R), G(_G), B(_B) {}
};

class Shape {
protected:
	std::vector<Dot> corners; //ò.ê âñå ôèãóðû ÷åòûðåõóãîëüíèêè
	double angle;// óãîë

	static size_t counter;// êîë-âî ôèãóð
	size_t id;//àéäè êàæäîé ôèóãðû

	Color color;//öâåò
	

	virtual void print(std::ostream& OS) const = 0; // Âûâîä

public:
	Shape(std::vector<Dot> points, Color color, double angle) :
		id(counter++), angle(angle), color(color), corners(points) {} //êîíñòêðóêòîð

	virtual ~Shape() {}//äåñòðóêòîð

	void move(Dot &new_center);//ïåðåäâèíóòü
	void scale(double scale );//ðàññòÿíóòü
	void rotate(double new_angle);//ïîâåðíóòü

	Color get_color() const; //ïîëó÷èòü öâåò
	void set_color(Color color);//óñòàíîâèòü öâåò
	Dot get_center();//ïîëó÷èòü öâåò
	size_t getId() const;//ïîëó÷èòü àéäè
	Dot& min_y(Dot& a, Dot& b) const;
	Dot& max_y(Dot& a, Dot& b) const;
	friend std::ostream& operator << (std::ostream& OS, const Shape& smth); // îïåðàòîð âûâîäà

	//Çàäàíèå
	bool common_side( Shape* other);

};

template <typename T>
bool float_comparison(T f1, T f2) {
	return (fabs(f1 - f2) <= std::numeric_limits<T>::epsilon());
}