#include <shape.h>
#include <math.h>
int Shape::id_counter = 0;
void Shape::setCoordinates(double newX, double newY) {
    s_x = newX;
    s_y = newY;
}
;
void Shape::setColor(const Color& newColor)
{
    s_color = newColor;
}

const Color Shape::getColor(){
    return s_color;
}

void Shape::rotate(double angle) {
    rotation_angle += angle;
}

int Shape::get_id(){
    return id;
}

void Sector::scale(double coefficient){
    s_radius *= coefficient;
}


void Star::scale(double coefficient){
    s_radius *=coefficient;
    s_radius2 *=coefficient;
}


void Star::rotate(double angle){
   rotation_angle += angle;
   dot1x =this->s_x + cos(rotation_angle/180*M_PI)*s_radius;
   dot1y =this->s_y - sin(rotation_angle/180*M_PI)*s_radius;
}

void Ellipse::scale(double coefficient) {
    e_a *= coefficient;
    e_b *= coefficient;
}
