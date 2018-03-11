//
// Created by katier on 07.03.18.
//
#include <cmath>
#include <ostream>
#ifndef UNTITLED_SHAPE_H
#define UNTITLED_SHAPE_H


struct Point{
    double x;
    double y;
    Point(double x,double y){
        this->x=x;
        this->y=y;
    }
    friend std::ostream &operator<<(std::ostream &os,  Point &point){
        os<<point.x<<" "<<point.y<<std::endl;
        return os;
    }
};

struct Colour{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    Colour(unsigned int red, unsigned int green,unsigned int blue){
        this->red=red;
        this->green=green;
        this->blue=blue;
    }
};

unsigned long long counter=0;


class Shape{
public:
    Shape(Colour colour):colour(colour){id=counter++;};
    Colour getColour(){
        return this->colour;
    }
    void setColour(Colour colour){
        this->colour=colour;
    }
    unsigned long long int getId(){
        return id;
    }
    virtual void move(Point newCoord) {}
    virtual void rotate(double fi){};
    virtual void scale(double k){}
    virtual void print(std::ostream& os){};

private:
    Colour colour;
    unsigned long long id;
protected:
        friend std::ostream &operator<<(std::ostream &os,  Shape &shape){
        shape.print(os);
        return os;
    }

};

#endif //UNTITLED_SHAPE_H
