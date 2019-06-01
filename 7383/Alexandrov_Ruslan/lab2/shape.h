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
	string color;
    virtual void move(vector<Points> points) = 0;
	virtual void rotate(int angle) = 0;
	virtual void scale(int coeff) = 0;
	virtual void set_color(string new_color) = 0;
	virtual string get_color() = 0;
	virtual ~Shape() {

	}
};

