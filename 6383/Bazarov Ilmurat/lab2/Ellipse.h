//
// Created by katier on 07.03.18.
//
#ifndef UNTITLED_ELLIPSE_H
#define UNTITLED_ELLIPSE_H
#include "Shape.h"

class Ellipse:public Shape{
public:
    Ellipse (Colour colour,double angle, Point center,double a,double b):Shape(colour),angle(angle),center(center),a(a),b(b){}
    void scale(double k) override{
        a*=k;
        b*=k;
    }
    void move (Point toNewCenter) override{
        center = toNewCenter;
    }
    void rotate(double angle) override {
        this->angle +=angle;
    }
    void print (std::ostream& os) override {
        os<<"\nEllipse\nid = "<<getId()<<"\na = "<<a<<"\nb = "<<b<<"\nangle = "<<angle<<"\nCenter:\n"<<center<<"Colour:\nblue = "
          <<getColour().blue<<"\ngreen = "<<getColour().green<<"\nred = " <<getColour().red<<std::endl;
    }

private:
    double a;
    double b;
    Point center;
    double angle;
};


#endif //UNTITLED_ELLIPSE_H
