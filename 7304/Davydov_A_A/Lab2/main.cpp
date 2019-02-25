#include <iostream>
#include <string>
#include <cmath>

using namespace std;

unsigned int next_id = 0;

enum Color{RED, ORANGE, YELLOW, GREEN, BLUE, DARK_BLUE, VIOLET};

//abstract class for next inheritance
class Shape
{
public:
    Shape(double x, double y, double angle, Color color) : x(x), y(y), color(color), id(next_id)
    {
        if(angle >= 360.0)
            this->angle = angle - int(angle / 360) * 360;
        else
            this->angle = angle;
        ++next_id;
    }

    ~Shape()
    {}

    //common methods
    void move_to(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    void rotate(double add_angle)
    {
        if(add_angle >= 360)
            add_angle = add_angle - int(add_angle / 360) * 360;
        if(angle + add_angle < 360.0)
            angle += add_angle;
        else
            angle = (angle + add_angle) - 360;
    }

    void setup_color(Color const &c)
    {
        color = c;
    }

    string get_color() const
    {
        switch(color)
        {
            case Color::RED:
            return "Color: RED";

            case Color::ORANGE:
            return "Color: ORANGE";

            case Color::YELLOW:
            return "Color: YELLOW";

            case Color::GREEN:
            return "Color: GREEN";

            case Color::BLUE:
            return "Color: BLUE";

            case Color::DARK_BLUE:
            return "Color: DARK BLUE";

            case Color::VIOLET:
            return "Color: VIOLET";

        default:
            return "Unknown color";
        }
    }

    friend std::ostream & operator <<(std::ostream &out, Shape &shape)
    {
        out << "Object id: " << shape.id << endl << "(x, y): " << shape.x << ", " << shape.y << endl << "Angle with ox: " << shape.angle <<  " degrees" << endl << shape.get_color();
        return out;
    }

    //abstract methods
    virtual void scaling(double k) = 0;

private:
    double x, y;
    double angle;
    Color color;
    unsigned int const id;
};


class EquilateralTriangle : public Shape
{
public:
    EquilateralTriangle(double x, double y, double angle, Color color,double a) : Shape(x, y, angle, color), a(a)
    {}

    ~EquilateralTriangle()
    {}

    void scaling(double k) override
    {
        a *= k;
    }

    friend std::ostream & operator << (std::ostream & out, EquilateralTriangle &eq_triangle)
    {
        out << dynamic_cast<Shape &>(eq_triangle) << endl << "Side a: " << eq_triangle.a;
        return out;
    }
private:
    //side of triangle
    double a;
};


class Triangle : public EquilateralTriangle
{
public:
    Triangle(double x, double y, double angle, Color color,double a, double b, double angle_a_b) : EquilateralTriangle (a, b, angle, color, a), b(b)
    {
        if(angle_a_b >= 360)
            this->angle_a_b = angle_a_b - int(angle_a_b / 360) * 360;
        else
            this->angle_a_b = angle_a_b;
        c = sqrt(a*a + b*b - 2*a*b*cos(angle_a_b * M_PI / 180));
    }

    ~Triangle()
    {}

    void scaling(double k) override
    {
        EquilateralTriangle::scaling(k);
        b *= k;
        c *= k;
    }

    friend std::ostream & operator << (std::ostream & out, Triangle &triangle)
    {
        out << dynamic_cast<EquilateralTriangle &>(triangle) << endl << "Side b: " << triangle.b << endl <<  "Side c:" << triangle.c;
        return out;
    }
private:
    double b;
    double angle_a_b;
    //this side compute by theorem of cos
    double c;
};


class Parallelogram : public Shape
{
public:
    Parallelogram(double x, double y, double angle, Color color, double a, double b, double angle_a_b) : Shape(x, y, angle, color), a(a), b(b), angle_a_b(angle_a_b)
    {}

    ~Parallelogram()
    {}

    void scaling(double k) override
    {
        a *= k;
        b *= k;
    }

    friend std::ostream & operator << (std::ostream & out, Parallelogram &p)
    {
        out << dynamic_cast<Shape &>(p) << endl << "Side a: " << p.a << endl << "Side b: " << p.b << endl <<  "Angel between a and b: " << p.angle_a_b;
        return out;
    }
private:
    double a;
    double b;
    //angle betweend sides a and b
    double angle_a_b;
};


int main()
{
    Triangle *shape = new Triangle(1, 1, 21.56, Color::RED, 3, 4, 450);
    cout << *shape << endl;
    shape->scaling(1.4);
    shape->move_to(2, 2.8);
    shape->rotate(721.45);
    shape->setup_color(Color::VIOLET);
    cout << *shape << endl;
    Parallelogram *p = new Parallelogram(2.5, 5.324, 184.434, Color::GREEN, 56.54, 78.7834, 76.54);
    cout << *p << endl;
    p->scaling(1.4);
    p->move_to(2, 2.8);
    p->rotate(721.45);
    p->setup_color(Color::YELLOW);
    cout << *p;
    Parallelogram a(0, 0, 0, Color::RED, 4, 12, 23),  b(0, 0, 0, Color::RED, 4, 12, 23);
    cout << endl;
    cout << a << endl << b << endl;
    Triangle c(1,2.534, 380.554, Color::GREEN, 54, 23, 73.2342);
    cout << c <<endl;
    return 0;
}
