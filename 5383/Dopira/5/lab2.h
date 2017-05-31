//
// Created by Xtail on 18.05.17.
//

#ifndef LAB2_H
#define LAB2_H

#include <iostream>
#include <ostream>
#include <functional>
#include <random>
#include <chrono>

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


    Shape(Color color) : color(color), id(counter++) {}//РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ
    virtual ~Shape(){} //РґРµСЃС‚СЂСѓРєС‚РѕСЂ
    virtual void move(int dx, int dy)=0;//РїРµСЂРµРјРµС‰РµРЅРёРµ
    virtual void rotate(int angle)=0; //РїРѕРІРѕСЂРѕС‚ РЅР° СѓРіРѕР»
    virtual void scale(int k)=0;//РјР°СЃС€Р°Р±РёСЂРѕРІР°РЅРёРµ РЅР° РєРѕСЌС„С„РёС†РёРµРЅС‚
    Color getColor() const;//СЂР°СЃРєСЂР°СЃРєР°
    void setColor(Color color);
    const bool operator ==(const Shape& other) const;
    friend std::ostream&operator<<(std::ostream& os, Shape& p);//РїРѕС‚РѕРє РІС‹РІРѕРґР°
    virtual void print(std::ostream& os) = 0;
protected:
    unsigned int id;

};








// Ellipse РЅР°СЃР»РµРґСѓРµС‚ Shape РєР°Рє public
class Ellipse : public Shape {
protected:
    unsigned int a; //РїРѕР»СѓРѕСЃРё
    unsigned int b;
    unsigned int fi; //СѓРіРѕР» РїРѕРІРѕСЂРѕС‚Р°
    Point center; //РєРѕРѕСЂРґРёРЅР°С‚С‹ С†РµРЅС‚СЂР°
public:
    Ellipse(Color color, Point center, unsigned int a=0, unsigned int b=0, unsigned int fi=0) : Shape(color), a(a), b(b), fi(fi%360), center(center) {}//РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ
    ~Ellipse() {}//РґРµСЃС‚СЂСѓРєС‚РѕСЂ

    // create Random Ellipse
    static Ellipse* createRandomShape();


    void move(int dx, int dy) override;//РїРµСЂРµРјРµС‰РµРЅРёРµ
    void rotate(int angle) override; //РїРѕРІРѕСЂРѕС‚ РЅР° СѓРіРѕР»
    void scale(int k) override;//РјР°СЃС€Р°Р±РёСЂРѕРІР°РЅРёРµ РЅР° РєРѕСЌС„С„РёС†РёРµРЅС‚
    Point getCenter() const;
    unsigned int getAAxis();
    unsigned int getBAxis();
    unsigned int getAngle();

    void print(std::ostream& os) override;
protected:

};








//SectorOfEllipse РЅР°СЃР»РµРґСѓРµС‚ РєР°Рє Ellipse.
//РўРµРј РЅРµ РјРµРЅРµРµ РІ SectorOfEllipse РёРјРµРµС‚СЃСЏ С‚РѕР»СЊРєРѕ РѕРґРЅР° РєРѕРїРёСЏ Shape!
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
    }//РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ
    ~SectorOfEllipse(){}//РґРµСЃС‚СЂСѓРєС‚РѕСЂ

    // create random Sector
    static SectorOfEllipse* createRandomShape();


    static void split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3);

    bool operator == (const SectorOfEllipse &other) const;

    void print(std::ostream& os) override;
protected:

};






//Parallelogram РЅР°СЃР»РµРґСѓРµС‚ Shape РєР°Рє public
class Parallelogram : public Shape {
private:
    Point a;
    Point b;
    Point c;
    Point d;
public:
    Parallelogram(Color color, Point a, Point b, Point c, Point d) : Shape (color), a(a), b(b), c(c), d(d) {}//РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ
    ~Parallelogram(){}//РґРµСЃС‚СЂСѓРєС‚РѕСЂ

    // create random Parallelogram
    static Parallelogram* createRandomShape();

    bool checkParallelogram(Point a, Point b, Point c, Point d);//РїСЂРѕРІРµСЂРєР° РЅР° РїР°СЂР°Р»Р»РµР»РѕРіСЂР°РјРј
    void move(int dx, int dy) override;//РїРµСЂРµРјРµС‰РµРЅРёРµ
    void rotate(int angle) override; //РїРѕРІРѕСЂРѕС‚ РЅР° СѓРіРѕР»
    void scale(int k) override;//РјР°СЃС€Р°Р±РёСЂРѕРІР°РЅРёРµ РЅР° РєРѕСЌС„С„РёС†РёРµРЅС‚

    void print(std::ostream& os) override;

protected:

};



#endif //OOPLAB5VALERIA_2_H
