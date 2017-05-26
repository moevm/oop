#pragma once
#ifndef Dot_h
#define Dot_h
class Dot
{
public:
	double x, y;
	Dot();
	Dot(double _x, double _y);
	double distance(const Dot &smth) const; // ????? ??????
	void rotate(double angle); //?????
	bool operator== (const Dot& smth) const;
	bool operator!= (const Dot& smth) const;
};

#endif
