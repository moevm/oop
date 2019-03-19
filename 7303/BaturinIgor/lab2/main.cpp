#include <QCoreApplication>
#include <iostream>
#include <math.h>

#define pi 3.14159265359

class Point {
public:
    double x;
    double y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    double length(Point& point)
    {
        return sqrt((x-point.x)*(x-point.x) + (y-point.y)*(y-point.y));
    }
    void rotate(double angle)
    {
        double newX = x;
        double newY = y;
        x = newX * cos(angle*pi/180) - newY * sin(angle*pi/180);
        y = newX * sin(angle*pi/180) + newY * cos(angle*pi/180);
    }
};

class Color {
public:
    Color() : red(0), green(0), blue(0) {}
    Color(short int red, short int green, short int blue) :red(red), green(green), blue(blue) {}
    /*void printColor() {
        std::cout << "Color: (" << this->red << ", " << this->green << ", " << this->blue << ")";
    }*/

    short int red;
    short int green;
    short int blue;
};

class Shape {
public:
    Shape() {}

    Shape(Color &color) : color(color) {
    }

    Color getColor() {
        return color;
    }

    void setColor(const Color& newColor) {
        color = newColor;
    }

    int getID() {
        id = count++;
        return id;
    }
    virtual void move(const Point& center) = 0;
    virtual void rotate(double angle = 0) = 0;
    virtual void scale(double coefficient = 1) = 0;
    Color color;
private:
    int id;
    int count = 0;
};

class Triangle : public Shape{
public:
    Triangle() : a(0), b(0), c(0) {}
    Triangle(Point& center ,Point& p1, Point& p2, Point& p3, Color color = Color())
        : center(center)
        , p1(p1)
        , p2(p2)
        , p3(p3)
        , Shape(color)
    {
        a = p1.length(p2);
        b = p2.length(p3);
        c = p3.length(p1);
    }

    Triangle(Color& color) : Shape(color) {}

    void scale(double coefficient) {
        this->coefficient = coefficient;
        this->p2.x = (this->p2.x-this->p1.x) * coefficient;
        this->p2.y = (this->p2.y-this->p1.y) * coefficient;
        this->p3.x = (this->p3.x-this->p1.x) * coefficient;
        this->p3.y = (this->p3.y-this->p1.y) * coefficient;
        a *= coefficient;
        b *= coefficient;
        c *= coefficient;
    }
    void rotate(double angle) {
        p1.rotate(angle);
        p2.rotate(angle);
        p3.rotate(angle);
    }
    void move(const Point& center) {
        double old_center_coordinates_x = this->center.x;
        double old_center_coordinates_y = this->center.y;
        this->p1.x = this->p1.x + center.x - old_center_coordinates_x;
        this->p1.y = this->p1.y + center.y - old_center_coordinates_y;
        this->p2.x = this->p2.x + center.x - old_center_coordinates_x;
        this->p2.y = this->p2.y + center.y - old_center_coordinates_y;
        this->p3.x = this->p3.x + center.x - old_center_coordinates_x;
        this->p3.y = this->p3.y + center.y - old_center_coordinates_y;
        this->center.x = center.x;
        this->center.y = center.y;
    }
    friend std::ostream& operator << (std::ostream &print, Triangle& triangle) {
        print << "Current center coordinates: A(" << triangle.center.x << ", " << triangle.center.y
              << ")\nCurrent points coordinates: P1(" << triangle.p1.x << ", " << triangle.p1.y << "), "
              << "P2(" << triangle.p2.x << ", " << triangle.p2.y << "), " << "P3(" << triangle.p3.x << ", "
              << triangle.p3.y << ")" << std::endl << "Current lengths of the sides of the triangle: a - "
              << triangle.a << ", b - " << triangle.b << ", c - " << triangle.c << std::endl
              << "Current ID: " << triangle.getID() << std::endl
              << "Current color: (" << triangle.color.red << ", " << triangle.color.green << ", " << triangle.color.blue << ")" << std::endl;
        return print;
    }

private:
    double coefficient = 1;
    double a;
    double b;
    double c;
    Point p1, p2, p3;
    Point center;
};

class Parallelogramm : public Shape {
public:
    Parallelogramm(Point& center, Point& p1, Point p2, Point& p3, Point& p4)
        : p1(p1), p2(p2), p3(p3), p4(p4)
        , center(center)
    {
        a = p1.length(p2);
        b = p2.length(p3);
        c = p3.length(p4);
        d = p4.length(p1);
        if (a != c && b != d) { std::cout << "ERROR"; exit(0); }
    }
    Parallelogramm(Parallelogramm& other)
        : a(other.a), b(other.b), c(other.c), d(other.d)
        , p1(other.p1), p2(other.p2), p3(other.p3), p4(other.p4)
        , coefficient(other.coefficient), center(other.center)
    {}

    Parallelogramm(Color& color) : Shape(color) {}

    void scale(double coefficient) {
        this->coefficient = coefficient;
        this->p2.x = (int)(this->p2.x - this->p1.x) * coefficient;
        this->p2.y = (int)(this->p2.y - this->p1.y) * coefficient;
        this->p3.x = (int)(this->p3.x - this->p1.x) * coefficient;
        this->p3.y = (int)(this->p3.y - this->p1.y) * coefficient;
        this->p4.x = (int)(this->p4.x - this->p1.x) * coefficient;
        this->p4.y = (int)(this->p4.y - this->p1.y) * coefficient;
        a *= coefficient;
        b *= coefficient;
        c *= coefficient;
        d *= coefficient;
    }

    void rotate(double angle) {
        p1.rotate(angle);
        p2.rotate(angle);
        p3.rotate(angle);
        p4.rotate(angle);
    }

    void move(const Point& center) {
        double old_center_coordinates_x = this->center.x;
        double old_center_coordinates_y = this->center.y;
        this->p1.x = this->p1.x + center.x - old_center_coordinates_x;
        this->p1.y = this->p1.y + center.y - old_center_coordinates_y;
        this->p2.x = this->p2.x + center.x - old_center_coordinates_x;
        this->p2.y = this->p2.y + center.y - old_center_coordinates_y;
        this->p3.x = this->p3.x + center.x - old_center_coordinates_x;
        this->p3.y = this->p3.y + center.y - old_center_coordinates_y;
        this->p4.x = this->p4.x + center.x - old_center_coordinates_x;
        this->p4.y = this->p4.y + center.y - old_center_coordinates_y;
        this->center.x = center.x;
        this->center.y = center.y;
    }

    friend std::ostream& operator << (std::ostream &print, Parallelogramm& parallelogramm) {
        print << "Current center coordinates: A(" << parallelogramm.center.x << ", " << parallelogramm.center.y
              << ")\nCurrent points coordinates: P1(" << parallelogramm.p1.x << ", " << parallelogramm.p1.y << "), "
              << "P2(" << parallelogramm.p2.x << ", " << parallelogramm.p2.y << "), " << "P3(" << parallelogramm.p3.x << ", "
              << parallelogramm.p3.y << "), " << "P4(" << parallelogramm.p4.x << ", " << parallelogramm.p4.y << ")"
              << std::endl << "Current lengths of the sides of the parallelogramm: a - "
              << parallelogramm.a << ", b - " << parallelogramm.b << ", c - " << parallelogramm.c << ", d - " << parallelogramm.d
              << std::endl << "Current ID: " << parallelogramm.getID() << std::endl
              << "Current color: (" << parallelogramm.color.red << ", " << parallelogramm.color.green << ", "
              << parallelogramm.color.blue << ")" << std::endl;
        return print;
    }
private:
    Point p1, p2, p3, p4;
    Point center;
    double coefficient = 1;
    double a, b, c, d;
};

/*%2F%2F Cool Class Diagram, [Shape|virtual void move;virtual void rotate;virtual void scale;Color color|int id; int count],[Shape|void scale()void rotare()void move()]<-, [Shape]<-[Triangle|void scale();void rotare();void move();friend std::ostream& operator|double coefficient; double a b c; Point p1 p2 p3 center], [Shape]<-[Parallelogramm|void scale(); void rotate(); void move(); friend std::ostream& operator|Point p1 p2 p3 p4 center; double coefficient; double a b c d], [Shape]<-[rightTriangle|]*/
class rightTriangle : public Shape {
public:
    rightTriangle() : a(0), b(0), c(0) {}
    rightTriangle(Point& center ,Point& p1, Point& p2, Point& p3, Color color = Color())
        : center(center)
        , p1(p1)
        , p2(p2)
        , p3(p3)
        , Shape(color)
    {
        a = p1.length(p2);
        b = p2.length(p3);
        c = p3.length(p1);
        if ((int)a != (int)b && (int)a != (int)c) { std::cout << "ERROR"; exit(0); }
    }
    rightTriangle(rightTriangle& other)
        : a(other.a), b(other.b), c(other.c)
        , p1(other.p1), p2(other.p2), p3(other.p3)
        , coefficient(other.coefficient), center(other.center)
    {}

    rightTriangle(Color& color) : Shape(color) {}

    void scale(double coefficient) {
        this->coefficient = coefficient;
        this->p2.x = (int)(this->p2.x-this->p1.x) * coefficient;
        this->p2.y = (int)(this->p2.y-this->p1.y) * coefficient;
        this->p3.x = (int)(this->p3.x-this->p1.x) * coefficient;
        this->p3.y = (int)(this->p3.y-this->p1.y) * coefficient;
        a *= coefficient;
        b *= coefficient;
        c *= coefficient;
    }
    void rotate(double angle) {
        p1.rotate(angle);
        p2.rotate(angle);
        p3.rotate(angle);
    }
    void move(const Point& center) {
        double old_center_coordinates_x = this->center.x;
        double old_center_coordinates_y = this->center.y;
        this->p1.x = this->p1.x + center.x - old_center_coordinates_x;
        this->p1.y = this->p1.y + center.y - old_center_coordinates_y;
        this->p2.x = this->p2.x + center.x - old_center_coordinates_x;
        this->p2.y = this->p2.y + center.y - old_center_coordinates_y;
        this->p3.x = this->p3.x + center.x - old_center_coordinates_x;
        this->p3.y = this->p3.y + center.y - old_center_coordinates_y;
        this->center.x = center.x;
        this->center.y = center.y;
    }
    friend std::ostream& operator << (std::ostream &print, rightTriangle& rightTriangle) {
        print << "Current center coordinates: A(" << rightTriangle.center.x << ", " << rightTriangle.center.y
              << ")\nCurrent points coordinates: P1(" << rightTriangle.p1.x << ", " << rightTriangle.p1.y << "), "
              << "P2(" << rightTriangle.p2.x << ", " << rightTriangle.p2.y << "), " << "P3(" << rightTriangle.p3.x << ", "
              << rightTriangle.p3.y << ")" << std::endl << "Current lengths of the sides of the rightTriangle: a - "
              << int(rightTriangle.a) << ", b - " << (int)rightTriangle.b << ", c - " << (int)rightTriangle.c << std::endl
              << "Current ID: " << rightTriangle.getID() << std::endl
              << "Current color: (" << rightTriangle.color.red << ", " << rightTriangle.color.green << ", " << rightTriangle.color.blue << ")" << std::endl;
        return print;
    }

private:
    Point p1, p2, p3;
    Point center;
    double coefficient = 1;
    double a;
    double b;
    double c;
};

int main()
{
   // QCoreApplication a(argc, argv);
    Color color(0, 10, 255);
    Point point1(2, 2);
    Point point2(5, 7);
    Point point3(6, 1);
    Point center((point1.x+point2.x+point3.x)/3, (point1.y+point2.y+point3.y)/3);
    Triangle t_1(center, point1, point2, point3, color);
    std::cout << "Triangle parameters after the announcement:" << std::endl << t_1 << std::endl;
    t_1.move(point2);
    t_1.setColor(Color(255, 255, 255));
    std::cout << "Triangle parameters after moving the center and change color:" << std::endl  << t_1 << std::endl;
    t_1.rotate(90);
    std::cout << "Triangle parameters after rotate:" << std::endl  << t_1 << std::endl;
    t_1.scale(1.5);
    t_1.setColor(Color(0, 0, 0));
    std::cout << "Triangle parameters after scale and change color:" << std::endl  << t_1 << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    Point center1(4, 4);
    Point p1(1, 2), p2(5, 2), p3(7, 6), p4(3, 6);
    Parallelogramm p_1(center1, p1, p2, p3, p4);
    p_1.setColor(Color(122, 240, 99));
    std::cout << "The parameters of the parallelogramm after the announcement:" << std::endl << p_1 << std::endl;
    p_1.move(point2);
    std::cout << "The parameters of the parallelogramm after moving the center:" << std::endl  << p_1 << std::endl;
    p_1.rotate(90);
    std::cout << "The parameters of the parallelogramm after rotate:" << std::endl  << p_1 << std::endl;
    p_1.scale(1.5);
    p_1.setColor(Color(0, 0, 0));
    std::cout << "The parameters of the parallelogramm after scale and change color:" << std::endl  << p_1 << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    Point pointR1(1, 1);
    Point pointR2(4, 6.1);
    Point pointR3(7, 1);
    Point centerR((pointR1.x+pointR2.x+pointR3.x)/3, (pointR1.y+pointR2.y+pointR3.y)/3);
    Triangle RT_1(centerR, pointR1, pointR2, pointR3, color);
    std::cout << "Triangle parameters after the announcement:" << std::endl << RT_1 << std::endl;
    RT_1.move(pointR2);
    RT_1.setColor(Color(13, 45, 129));
    std::cout << "Triangle parameters after moving the center and change color:" << std::endl  << RT_1 << std::endl;
    RT_1.rotate(270);
    std::cout << "Triangle parameters after rotate:" << std::endl  << RT_1 << std::endl;
    RT_1.scale(2.0);
    RT_1.setColor(Color(12, 12, 12));
    std::cout << "Triangle parameters after scale and change color:" << std::endl  << RT_1 << std::endl;
    system("pause");
    return 0;
}
