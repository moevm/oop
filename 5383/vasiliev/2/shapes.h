#ifndef SHAPES_H
#define SHAPES_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <exception>
#include <string>


class Shape
{
public:
    virtual ~Shape() {}
    void setColor(unsigned int color)
    {
        this->color = color;
    }
    unsigned int getColor() const
    {
        return this->color;
    }
    void setPosition(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    void getPosition(double &x, double &y) const
    {
        x = this->x;
        y = this->y;
    }
    void setAngle(double angle)
    {
        this->angle = fmod(angle, 2 * M_PI);
    }
    double getAngle() const
    {
        return this->angle;
    }
    virtual void stretch(double q) = 0;
    unsigned int getId() const
    {
        return this->id;
    }
    virtual std::ostream& print(std::ostream& stream) const
    {
        stream << "at [" << x << ";" << y << "], angle [" << angle << "], "
               << "color [" << std::setw(8) << std::setfill('0') << std::hex << color << "]";
        return stream;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Shape& shape)
    {
        return shape.print(stream);
    }

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;

    class ConstructError: public std::logic_error
    {
    public:
        ConstructError(const std::string& what_arg) : std::logic_error(what_arg) {};
        ConstructError(const char* what_arg) : std::logic_error(what_arg) {};
    };

protected:
    Shape(double x = 0, double y = 0,
          double angle = 0, unsigned int color = 0x000000FF)
        : x(x), y(y),
          color(color),
          id(++counter)
    {
        setAngle(angle);
    }

private:
    static unsigned int counter;
    const unsigned int id;
protected:
    double x;
    double y;
    double angle;
    unsigned int color;
};

class Rectangle: public Shape
{
public:
    Rectangle(double length, double width,
              double x = 0, double y = 0,
              double angle = 0, unsigned int color = 0x000000FF)
        : length(length), width(width),
          Shape(x, y, angle, color)
    {
        if (!length) {
            throw Shape::ConstructError("Incorrect length");
        }
        if (!width) {
            throw Shape::ConstructError("Incorrect width");
        }
    }

    virtual ~Rectangle() {}

    double getLength()
    {
        return this->length;
    }

    double getWidth()
    {
        return this->width;
    }

    void stretch(double q) override
    {
        this->length *= q;
        this->width *= q;
    }

    void stretchWidth(double q)
    {
        this->width *= q;
    }

    void stretchLength(double q)
    {
        this->length *= q;
    }

    double getArea() const override
    {
        return length * width;
    }
    double getPerimeter() const override
    {
        return 2 * (length + width);
    }

    std::ostream& print(std::ostream& stream) const override
    {
        stream << "Rectangle [" << length << "x" << width << "] ";
        Shape::print(stream);
        return stream;
    }

protected:
    double length;
    double width;
};

class Square: public Rectangle
{
public:
    Square(double side,
           double x = 0, double y = 0,
           double angle = 0, unsigned int color = 0x000000FF)
        : Rectangle(side, side, x, y, angle, color)
    {
    }

    virtual ~Square() {}

    void stretchLength(double q)
    {
        this->stretch(q);
    }

    void stretchWidth(double q)
    {
        this->stretch(q);
    }

    std::ostream& print(std::ostream& stream) const override
    {
        stream << "Square [" << length << "] ";
        Shape::print(stream);
        return stream;
    }
};

class Ellipse: public Rectangle
{
public:
    using Rectangle::Rectangle;
    virtual ~Ellipse() {}
    double getArea() const override
    {
        return M_PI * width * length / 4;
    }
    double getPerimeter() const override
    {
        return (2 * M_PI * width * length + 4 * fabs(width - length)) / (width + length);
    }

    std::ostream& print(std::ostream& stream) const override
    {
        stream << "Ellipse [" << length << "x" << width << "] ";
        Shape::print(stream);
        return stream;
    }
};

unsigned int Shape::counter = 0;

#endif
