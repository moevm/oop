//
// Created by Xtail on 18.05.17.
//

#ifndef OOPLAB5VALERIA_2_H
#define OOPLAB5VALERIA_2_H

#include <iostream>
#include <ostream>
#include <functional>
#include <random>


const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
static const int magicborder = 1 << 8;


struct Point {
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator==(const Point &p) const { return (x == p.x && y == p.y); }
    friend std::ostream& operator<<(std::ostream &os, const Point& p)
    {
        os << "(" << p.x << "; " << p.y << ")";
        return os;
    }
};

class Color {
public:
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    Color(unsigned int _red, unsigned int _green, unsigned int _blue) :
            red(_red), green(_green), blue(_blue) {}

    bool operator==(const Color &other) const {
        return (red == other.red &&
                green == other.green &&
                blue == other.blue);
    }

    friend std::ostream& operator<<(std::ostream &os, const Color& p)
    {
        os << "(" << p.red << "; " << p.green << "; " << p.blue << ")";
        return os;
    }
};
class Shape{
private:
    static size_t counter;
    Color color;
public:
    // create random Shape
    static Shape* createRandomShape();


    Shape(Color color) : color(color), id(counter++) {}//конструктор
    virtual ~Shape(){} //деструктор
    virtual void move(int dx, int dy)=0;//перемещение
    virtual void rotate(int angle)=0; //поворот на угол
    virtual void scale(int k)=0;//масшабирование на коэффициент
    Color getColor() const;//раскраска
    void setColor(Color color);
    friend std::ostream&operator<<(std::ostream& os, Shape& p);//поток вывода
    virtual void print(std::ostream& os) = 0;
protected:
    unsigned int id;

};








// Ellipse наследует Shape как public
class Ellipse : public Shape {
protected:
    unsigned int a; //полуоси
    unsigned int b;
    unsigned int fi; //угол поворота
    Point center; //координаты центра
public:
    Ellipse(Color color, Point center, unsigned int a=0, unsigned int b=0, unsigned int fi=0) : Shape(color), a(a), b(b), fi(fi%360), center(center) {}//конструктор
    ~Ellipse() {}//деструктор

    // create Random Ellipse
    static Ellipse* createRandomShape();


    void move(int dx, int dy) override;//перемещение
    void rotate(int angle) override; //поворот на угол
    void scale(int k) override;//масшабирование на коэффициент
    Point getCenter() const;
    unsigned int getAAxis();
    unsigned int getBAxis();
    unsigned int getAngle();

    void print(std::ostream& os) override;
protected:

};








//SectorOfEllipse наследует как Ellipse.
//Тем не менее в SectorOfEllipse имеется только одна копия Shape!
class SectorOfEllipse : public Ellipse {
private:
    int f1;
    int f2;
public:
    SectorOfEllipse (Color color = Color(0, 0, 0), Point center = Point(0, 0), int a=0, int b=0, unsigned int fi=0, unsigned int f1 = 0, unsigned int f2 = 0) :
            Ellipse (color,center,a,b, fi),
            f1(f1%360),
            f2(f2%360)
    {
    }//конструктор
    ~SectorOfEllipse(){}//деструктор

    // create random Sector
    static SectorOfEllipse* createRandomShape();


    static void split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3);

    bool operator == (const SectorOfEllipse &other) const;

    void print(std::ostream& os) override;
protected:

};






//Parallelogram наследует Shape как public
class Parallelogram : public Shape {
private:
    Point a;
    Point b;
    Point c;
    Point d;
public:
    Parallelogram(Color color, Point a, Point b, Point c, Point d) : Shape (color), a(a), b(b), c(c), d(d) {}//конструктор
    ~Parallelogram(){}//деструктор

    // create random Parallelogram
    static Parallelogram* createRandomShape();

    bool checkParallelogram(Point a, Point b, Point c, Point d);//проверка на параллелограмм
    void move(int dx, int dy) override;//перемещение
    void rotate(int angle) override; //поворот на угол
    void scale(int k) override;//масшабирование на коэффициент

    void print(std::ostream& os) override;

protected:

};



#endif //OOPLAB5VALERIA_2_H
