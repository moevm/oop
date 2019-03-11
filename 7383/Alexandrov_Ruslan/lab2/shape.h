#pragma once
#include <iostream>
#include <vector>

using namespace std;
struct Points {
    double x;
    double y;
};

class Shape {
public:
	virtual void move(vector<Points> points) {};
	virtual void rotate(int angle) {};
	virtual void scale(int coeff) {};
	virtual void set_color(string new_color) {};
	virtual string get_color() {};
	string color;
};

