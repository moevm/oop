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
