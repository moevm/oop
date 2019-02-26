// 10 вариант: Прямоугольник, Трапеция, Равнобедренная трапеция.

#include <iostream>
#include <math.h>
using namespace std;
unsigned ID = 1;

class Point {
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double getX() const {return x;}
    double getY() const {return y;}
    void setY(double newY) {y = newY;}
    
    Point &operator = (Point const &newPoint) = default;
    
    friend ostream &operator << (ostream &out, Point const &point) {
        out << "(x = " << point.x << ",y = " << point.y << ")";
        return out;
    }
    
private:
    double x, y;
};

class Color {
public:
    Color(unsigned int red, unsigned int green, unsigned int blue) : RED(red), GREEN(green), BLUE(blue) {}
    
    Color() {}
    
    Color greeen() {
        return Color(0, 255, 0);
    }
    
    Color black() {
        return Color(0, 0, 0);
    }
    
    Color white() {
        return Color(255, 255, 255);
    }
    
    friend ostream &operator << (ostream &out, Color const &c) {
        out << "(R = " << c.RED << ", G = " << c.GREEN << ", B = " << c.BLUE << ")";
        return out;
    }
    
private:
    unsigned int RED, GREEN, BLUE;
};

class Shape {
public:
    Shape(Point point = Point(0, 0), Color col = Color(255, 255, 255), double ang = 0)
    : centerOffset(point), color(col), angle(ang), id(ID++) {}
    
    virtual void mv(Point mvPoint) {
        centerOffset = mvPoint;
    }
    
    virtual void rotate(double a) {
        angle += a;
    }
    
    virtual void setColor(Color c) {
        color = c;
    }
    
    virtual Color getColor() {
        return color;
    }
    
    double getAngle() {
        return angle;
    }
    
    void setAngle(double a) {
        angle = a;
    }
 
    virtual void scale(double) = 0;
    
    friend ostream &operator << (ostream &out, Shape const &shape) {
        cout << "ID: " << shape.id << endl <<
        "COLOR: " << shape.color << endl <<
        "CENTER OFFSET: " << shape.centerOffset << endl <<
        "ANGLE: " << shape.angle << endl;
        
        return out;
    }
    
private:
    Color color;
    Point centerOffset;
    double angle;
    unsigned id;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height, double angle = 0, Color color = Color(255, 255, 255), Point point = Point(0.0, 0.0))
    : Shape(point, color, angle), width(width), height(height) {}
    
    void scale(double s) override {
        height *= s;
        width *= s;
    }
    
    friend ostream &operator<<(ostream &out, Rectangle const &rectangle) {
        cout << dynamic_cast<Shape const &>(rectangle) << "SHAPE: Rectangle" << endl <<
        "WIDTH: " << rectangle.width << endl <<
        "HEIGHT: " << rectangle.height << endl;
        
        return out;
    }
    
private:
    double width, height;
};

class Line {
public:
    Line(Point s, Point f): start(s), finish(f) {}
private:
    Point start;
    Point finish;
};

class Trapezium : public Shape {
public:
    Trapezium(Point topLineCenter, Point bottomLineCenter, double topLineWidth, double bottomLineWidth, double angle = 0.0, Color color = Color(255, 255, 255), Point center = Point(0.0, 0.0))
    : Shape(center, color, angle), topLineCenter(topLineCenter), bottomLineCenter(bottomLineCenter), topLineWidth(topLineWidth), bottomLineWidth(bottomLineWidth) {}
    
    void scale(double s) override {
        topLineWidth *= s;
        bottomLineWidth *= s;
        topLineCenter.setY(topLineCenter.getY() * s);
    }
    
    void rotate(double a) override {
        setAngle(getAngle() + a);
        
        double X = topLineCenter.getX();
        double Y = topLineCenter.getY();
        X -= bottomLineCenter.getX();
        Y -= bottomLineCenter.getY();
        
        double newX = X * cos(a) - Y * sin(a);
        double newY = X * sin(a) + Y * cos(a);
        
        topLineCenter = Point(newX + bottomLineCenter.getX(), newY + bottomLineCenter.getY());
    }
    
    friend ostream &operator << (ostream &out, Trapezium const &trap) {
        cout << dynamic_cast<Shape const &>(trap) << "SHAPE: Trapezium" << endl <<
        "TOP LINE WIDTH: " << trap.topLineWidth << ", "<<
        "CENTER: " << trap.topLineCenter << endl <<
        "BOTTOM LINE WIDTH: " << trap.bottomLineWidth << ", " <<
        "CENTER: " << trap.bottomLineCenter << endl;
        
        return out;
    }
    
private:
    Point topLineCenter;
    Point bottomLineCenter;
    double topLineWidth;
    double bottomLineWidth;
};

class RightTrapezium : public Shape {
public:
    RightTrapezium(double height, double topLineWidth, double bottomLineWidth, double angle = 0.0, Color color = Color(255, 255, 255), Point center = Point(0.0, 0.0))
    : Shape(center, color, angle), height(height), topLineWidth(topLineWidth), bottomLineWidth(bottomLineWidth) {}
    
    void scale(double s) override {
        topLineWidth *= s;
        bottomLineWidth *= s;
        height *= s;
    }
    
    friend ostream &operator << (ostream &out, RightTrapezium const &trap) {
        cout << dynamic_cast<Shape const &>(trap) << "SHAPE: RightTrapezium" << endl <<
        "TOP LINE WIDTH: " << trap.topLineWidth << endl <<
        "BOTTOM LINE WIDTH: " << trap.bottomLineWidth << endl <<
        "HEIGHT: " << trap.height << endl;
        return out;
    }
    
private:
    double height;
    double topLineWidth;
    double bottomLineWidth;
};

int main() {
    Rectangle rect(99.5, 200.0);
    Trapezium trap(Point(60.0, 30.0), Point(70.0, 0.0), 30.0, 100.0);
    RightTrapezium rtrap(10.0, 20.0, 60.0);
    
    cout << "BEFORE: \n\n";
    cout << rect << endl;
    cout << trap << endl;
    cout << rtrap <<endl;
    
    cout << "\nAFTER: \n\n" ;
    rect.rotate(100.0);
    rect.scale(3.5);
    rect.setColor(Color().greeen());
    
    trap.rotate(10.0);
    trap.mv(Point(10.0, -5.0));
    trap.scale(0.33);
    trap.setColor(Color(40.0, 5.0, 0.0));
    
    rtrap.rotate(-40.0);
    rtrap.mv(Point(12.0, -20.0));
    rtrap.setColor(Color().white());
    
    cout << rect << endl;
    cout << trap << endl;
    cout << rtrap <<endl;
    
    return 0;
}
