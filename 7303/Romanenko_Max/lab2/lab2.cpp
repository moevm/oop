#include <iostream>
#include <vector>
#include <cmath>



struct Point {
    Point(double x = 0, double y = 0): x(x), y(y) {}
    Point(const Point& other):x(other.x), y(other.y){}


    double x;
    double y;
};

std::ostream& operator<<(std::ostream& out, Point& p) {
  return out << "{x:" << p.x << ", y:" << p.y << "}";
}

struct Color{

    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0):red(r),green(g),blue(b){}
    Color(const Color& other):red(other.red),green(other.green),blue(other.blue){}

    void set(unsigned char r, unsigned char g, unsigned char b){
        red = r;
        green = g;
        blue = b;
    }

    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

std::ostream& operator<<(std::ostream& out, Color& n) {
  return out << "(" << (int)n.red << "," << (int)n.green << "," << (int)n.blue << ")";
}

class Shape{
public:

    virtual void move(const Point& p){
        double x_diff = p.x - pos.x;
        double y_diff = p.y - pos.y;
        pos.x += x_diff;
        pos.y += y_diff;
        for(auto& el : points){
            el.x += x_diff;
            el.y += y_diff;
        }
    }

    virtual void scale(double scale){
        this->Scale *= scale;
        for(auto& el : points){
            double x = el.x - pos.x;
            double y = el.y - pos.y;
            el.x = pos.x + x*scale;
            el.y = pos.y + y*scale;
        }
    }

    virtual void turn(double angle){

        this->angle = fmod((this->angle + angle),360);
        for(auto& el : points){
            double x = el.x - pos.x;
            double y = el.y - pos.y;
            el.x =pos.x + x*cos(this->angle*M_PI/180) - y*sin(this->angle*M_PI/180);
            el.y =pos.y + x*sin(this->angle*M_PI/180) + y*cos(this->angle*M_PI/180);
        }
    }

    friend std::ostream& operator<<(std::ostream& out, Shape& shape){
        out << "Id: " << shape.id << std::endl;
        out << "Coordinates of extreme points: ";
        for(auto& el : shape.points){
           out << el << " ";
        }
        out << std::endl << "Color: " << shape.color;
        out << std::endl << "Scale: " << shape.Scale << "x";
        out << std::endl << "Angle: " << shape.angle << " degree";
        return out;


    }

    void setColor(Color color) {
      this->color.set(color.red,color.green,color.blue);
    }
    Color getColor() {
      return color;
    }

protected:
    Shape(const Point& position)
        :pos(position){
        static unsigned int id_counter = 1;
        id = id_counter++;

    }

    Point pos;
    Color color;
    unsigned int id;
    double angle = 0;
    double Scale = 1;
    std::vector<Point> points;

};


class rightTriangle: public Shape{
public:
    rightTriangle(const Point& p, double kat1, double kat2)
        :Shape(p)
    {
        sides.push_back(kat1);
        sides.push_back(kat2);
        sides.push_back(sqrt(kat1*kat1 + kat2*kat2));
        points.push_back(p);
        points.push_back(Point(p.x+kat1,p.y));
        points.push_back(Point(p.x,p.y+kat2));
    }

    friend std::ostream& operator<< (std::ostream& out, const rightTriangle& rTr) {

        out << "----right triangle----" << std::endl << "Sides: ";
        out << rTr.sides.at(0) << "x" << rTr.sides.at(1) << "x" << rTr.sides.at(2) << std::endl;
        out << (Shape&)rTr;
        return out;
    }
protected:
    std::vector<int> sides;
};



class Square: public Shape{
public:
    Square(const Point& p, double side)
        :Shape(p)
    {
        points.push_back(Point(p.x-side/2,p.y+side/2));
        points.push_back(Point(p.x+side/2,p.y-side/2));
    }
    friend std::ostream& operator<< (std::ostream& out, const Square& square) {

        out << "----Square----" << std::endl << "Side: " << fabs(square.points.at(0).x - square.points.at(1).x) << std::endl;
        out << (Shape&)square;
        return out;
    }

};


class isoscelesTriangle:public Shape{
public:
    isoscelesTriangle(const Point& p1, const Point& p2, const Point& p3)
        :Shape(Point((p1.x+p2.x+p3.x)/3, (p1.y+p2.y+p3.y)/3))
    {
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        sides.push_back(sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)));
        sides.push_back(sqrt((p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y)));
        sides.push_back(sqrt((p3.x - p1.x)*(p3.x - p1.x) + (p3.y - p1.y)*(p3.y - p1.y)));
        double a = sides.at(0);
        double b = sides.at(1);
        double c = sides.at(2);
        if ((a+b)<=c || (a+c)<=b || (c+b)<= a){
            throw std::logic_error("Not a triangle");
        }
        if (!((a==b)||(a==c)||(b==c)))
            throw std::logic_error("Not a isosceles triangle");


    }
    friend std::ostream& operator<< (std::ostream& out, const isoscelesTriangle& iTr) {

        out << "----Isosceles triangle----" << std::endl << "Sides: ";

        out << iTr.sides.at(0) << "x" << iTr.sides.at(1) << "x" << iTr.sides.at(2) << std::endl;
        out << (Shape&)iTr;
        return out;
    }
protected:
    std::vector<int> sides;
};


int main(){
    Square kv({0,0},6);
    kv.scale(3);
    kv.move({0,2});
    std::cout << kv << std::endl;
    rightTriangle rt({10,5},6,4);
    rt.turn(90);
    rt.setColor(Color(234,32,145));
    std::cout << rt << std::endl;
    isoscelesTriangle it({1,3},{-2,-2},{4,-2});
    std::cout << it << std::endl;

}
