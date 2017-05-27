#pragma once

class Color {
private:
    unsigned long color;

public:
    Color(unsigned long n = 0)
        : color(n)
    {
    }
    void set(unsigned long newcolor)
    {
        color = newcolor;
    }
    unsigned long get()
    {
        return color;
    }
    friend std::ostream& operator<<(std::ostream& os, const Color& tr)
    {
        os << "#" << std::setw(6) << std::setfill('0') << std::hex << tr.color;
        return os;
    }
};
class Point {
private:
    double X, Y;

public:
	Point(double Xn = 0, double Yn = 0): X(Xn), Y(Yn){}

    Point operator+(Point const& t) const;
    double getX()
    {
        return X;
    }
    double getY()
    {
        return Y;
    }
    void setX(double a)
    {
        X = a;
    }
    void setY(double a)
    {
        Y = a;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& tr)
    {
        os << "(" << tr.X << "," << tr.Y << ")";
        return os;
    }
};
Point Point::operator+(Point const& t) const
{
    Point a(X + t.X, Y + t.Y);
    return a;
}
class Shape {
public:
	Shape(): color(Color(0)){}

    void move(Point newcord)
    {
        cord = newcord;
    }
    void rotate(double angle);
    void scale(double coef);
    Color getColor()
    {
        return color;
    }
    void setColor(Color newcolour)
    {
        color = newcolour;
    }

protected:
    std::vector<Point> point;
    Point cord;
    Color color;
};
void Shape::scale(double coef)
{
    for (int i = 0; i < point.size(); i++) {
        point[i].setX(point[i].getX() * coef);
        point[i].setY(point[i].getY() * coef);
    }
}
void Shape::rotate(double angle)
{
    for (int i = 0; i < point.size(); i++) {
        point[i].setX(point[i].getX() * cos(angle)
            - point[i].getY() * sin(angle));
        point[i].setY(point[i].getX() * sin(angle)
            + point[i].getY() * cos(angle));
    }
}

//===Треугольник===
class Triangle : public Shape {
private:
	double Leng;
public:
	double get_angle();
    Triangle(double leng, Point topp)
    {
        cord = Point(0, 0);
        point.push_back(Point(leng, 0));
        point.push_back(topp);
		this->Leng = leng;
    }
    friend std::ostream& operator<<(std::ostream& os, const Triangle& tr)
    {
        os << "Triangle(" << tr.cord << ";"
           << tr.cord + tr.point[0] << ";" << tr.cord + tr.point[1]
           << "):" << tr.color;
        return os;
    }
};
double Triangle::get_angle(){
	return this->Leng;
}

//===Ромб===
class Rhombus : public Shape {
private:
	double Leng, Angle;
public:
    Rhombus(double leng, double angle);
	double get_agnle();
	double get_leng();
    friend std::ostream& operator<<(std::ostream& os, const Rhombus& tr)
    {
        os << "Rhombus(" << tr.cord << ";"
           << tr.cord + tr.point[0] << ";" << tr.cord + tr.point[1]
           << ";" << tr.cord + tr.point[2] << "):" << tr.color;
        return os;
    }
};
Rhombus::Rhombus(double leng, double angle)
{
    cord = Point(0, 0);
    point.push_back(Point(leng, 0));
    point.push_back(Point(leng * (cos(angle) + 1), leng * sin(angle)));
    point.push_back(Point(leng * cos(angle), leng * sin(angle)));
	this->Leng = leng;
	this->Angle = angle;
}
double Rhombus::get_agnle()
{
	return this->Angle;
}
double Rhombus::get_leng()
{
	return this->Leng;
}

//===Параллелограмм===
class Parallelogram : public Shape {
private:
	double Width, Height;
public:
    Parallelogram(double width, double height);
	double get_width();
	double get_heigth();
    friend std::ostream& operator<<(std::ostream& os, const Parallelogram& tr)
    {
        os << "Parallelogram(" << tr.cord << ";"
           << tr.cord + tr.point[0] << ";" << tr.cord + tr.point[1]
           << ";" << tr.cord + tr.point[2] << "):" << tr.color;
        return os;
    }
};
Parallelogram::Parallelogram(double width, double height)
{
    cord = Point(0, 0);
    point.push_back(Point(width, 0));
    point.push_back(Point(width, height));
    point.push_back(Point(0, height));
	this->Width = width;
	this->Height = height;
}
double Parallelogram::get_width()
{
	return this->Width;
}
double Parallelogram::get_heigth()
{
	return this->Height;
}