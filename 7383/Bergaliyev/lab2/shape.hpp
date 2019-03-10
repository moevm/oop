#pragma once
#include <cmath>
#include <iostream>
#define eps 0.000000000001

struct Color{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    Color(unsigned char red, unsigned char green, unsigned char blue)
     : red(red), green(green), blue(blue) {}
};

std::ostream & operator<<(std::ostream & ostream, Color const & color);

struct Point{
    double x;
    double y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    double distance(Point const & p) const {
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y-p.y));
    }
};

std::ostream & operator<<(std::ostream & ostream, Point const & p);

class Shape{
public:
    virtual void scale(double scale_ratio) = 0;
    virtual void relocate(Point p) = 0;
    virtual void rotate(double angle) = 0;
    virtual std::ostream & print(std::ostream & ostream) const = 0;
    Color get_color() const {
	return color;
    }
    void set_color(Color new_color){
	color = new_color;
    }
    unsigned int get_id() const{
	return id;
    }
protected:
    Shape(Color color, Point center) : color(color), center(center), id(count) {
	++count;
    }
    Shape(Color color) : color(color), id(count) {
	++count;
    }
    Color color;
    Point center; //точка пересечения диагоналей
private:
    unsigned int id;
    static unsigned int count;
};

std::ostream & operator<<(std::ostream & ostream, Shape const & shape);
