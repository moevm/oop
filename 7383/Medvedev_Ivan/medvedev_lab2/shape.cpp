#include "shape.h"

int Shape::counter = 0;

Shape::Shape():id(counter),angle(0), colour(), point(){
    counter++;
}

Shape::Shape(double _angle, RGB _colour, Point _point):id(counter), angle(_angle), colour(_colour), point(_point){
    counter++;
}

double Shape::get_angle(){
    return angle;
}

Point Shape::get_cntr(){
    return point;
}

int Shape::get_id(){
    return id;
}

RGB Shape::get_colour(){
    return colour;
}

void Shape::set_colour(const RGB _colour){
    colour.red = _colour.red;
    colour.green = _colour.green;
    colour.blue = _colour.blue;
}

void Shape::set_cntr(const Point cntr){
    point.x = cntr.x;
    point.y = cntr.y;
}

Shape::~Shape(){
    points.clear();
}

void Shape::move(const Point p){
    double delta = p.x - point.x;
    double eps = p.y - point.y;
    point.x += delta;
    point.y += eps;
    for(auto& pnt : points){
        pnt.x += delta;
        pnt.y += eps;
    }
}

void Shape::rotate(int _angle)
{
    angle += _angle;
    _angle %= 360;
    double rad = _angle*M_PI/180;
    double x, y;
    for(auto& pnt : points){
        x = pnt.x;
        y = pnt.y;
        pnt.x =(x - point.x) * cos(rad) - (y - point.y) * sin(rad) + point.x;
        pnt.y = (x - point.x) * sin(rad) - (y - point.y) * cos(rad) + point.y;
    }

}
std::ostream& operator<<(std::ostream& out, Shape& shape){
    out << "!Information!"<<std::endl;
    out << "Center: " <<"("<< shape.get_cntr().x << ";" << shape.get_cntr().y << ")" << std::endl;
    out << "Colour (RGB): " <<"("<< shape.get_colour().red << ","<< shape.get_colour().green << ","<< shape.get_colour().blue << ")" << std::endl;
    out << "Angle: " << shape.get_angle() << std::endl;
    out << "Id: " << shape.get_id() << std::endl;
    out << "Area: " << shape.area() << std::endl;
    return out;
}
