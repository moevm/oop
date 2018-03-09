#include "Shape.h"
#include <cmath>
unsigned long instances=0;

Shape::Shape(std::string color):id(instances++),color(color){}
unsigned long Shape::getId() const { return id;}

void Shape::translate(double x, double y){
    applyForAnyPoint([x,y](Point& p) -> void {p.x+=x;p.y+=y;});
}

void Shape::rotate(double angle){
    applyForAnyPoint([angle](Point& p) -> void {
        double x= p.x*cos(angle)-p.y*sin(angle);
        double y= p.x*sin(angle)+p.y*cos(angle);
        p.x=x;
        p.y=y;
    });
}

void Shape::scale(double scale){
    applyForAnyPoint([scale] (Point& p) -> void {p.x*=scale;p.y*=scale;});
}

Color const & Shape::getColor() const{
    return color;
}

void Shape::setColor(Color const &color){
    this->color=color;
}

std::ostream &operator << (std::ostream &os, Shape const &f) {
    os<<f.toString();
    return os;
}