#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <cmath>
#include <iostream>

#define PI 3.14159265359

class rgb
{
protected:
    int red;
    int green;
    int blue;

public:
    rgb(){}
    rgb(int red, int green, int blue) : red(red), green(green), blue(blue){}

    void setColor(int red, int green, int blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    int getRed()
    {
        return red;
    }

    int getGreen()
    {
        return green;
    }

    int getBlue()
    {
        return blue;
    }
};


class Point
{
protected:
    double x;
    double y;

public:
    Point(int x=0, int y=0) : x(x), y(y){}

    void setPoint(double otherX, double otherY)
    {
        x = otherX;
        y = otherY;
    }

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }

    void setX(double X)
    {
        x = X;
    }

    void setY(double Y)
    {
        y = Y;
    }
};


class Shape
{
protected:
    unsigned long int id;
    Point center;
    rgb color;

public:
    static unsigned long int count;
    virtual void move(double x, double y) = 0;
    virtual void turn(double deg) = 0;
    virtual void scale(double coeff) = 0;
    virtual std::ostream& printShape(std::ostream &out, Shape &shape) = 0;
    virtual void show() = 0;

    Shape()
    {
        count++;
        id = count;
    }

    Shape(rgb color) : Shape()
    {
        this->color = color;
    }

    void setMainCenter(double x, double y)
    {
        center.setPoint(x, y);
    }

    Point getMainCenter(){
        return center;
    }

    rgb getShapeColor()
    {
        return color;
    }

    unsigned long int getId(){
        return id;
    }

    friend std::ostream& operator<< (std::ostream& out, Shape &shape)
    {
        return shape.printShape(out, shape);
    }
};


class Triangle : public Shape
{
protected:
    Point one;
    Point two;
    Point three;

public:
    Triangle(){}
    Triangle(rgb color, double x1, double y1, double x2, double y2, double x3, double y3) : Shape(color)
    {
        one.setPoint(x1,y1);
        two.setPoint(x2,y2);
        three.setPoint(x3,y3);
    }

    void setCenter(){
        double x12 = (one.getX() + two.getX())/2;
        double y12 = (one.getY() + two.getY())/2;
        double x13 = (one.getX()+three.getX())/2;
        double y13 = (one.getY()+three.getY())/2;
        double expression1 = y12*(three.getX()-x12)/(three.getY()-y12)/(two.getX()-x13) - x12/(two.getX()-x13) + x13/(two.getX()-x13) - y13/(two.getY()-y13);
        double expression2 = (three.getX()-x12)/(three.getY()-y12)/(two.getX()-x13) - 1/(two.getY()-y13);
        double y = expression1/expression2;
        double x = (y-y12)*(three.getX()-x12)/(three.getY()-y12) + x12;
        setMainCenter(x,y);
    }

    void show() override
    {
        QGraphicsScene *scene = new QGraphicsScene;
        scene->setSceneRect(-500, -500, 1000, 1000);
        scene->addLine(0,-500,0,500);
        scene->addLine(-500,0,500,0);

        rgb clr = getShapeColor();
        QColor color(clr.getRed(), clr.getGreen(), clr.getBlue());
        QPen pen;
        pen.setColor(color);
        pen.setWidth(3);

        scene->addLine(one.getX(), one.getY(), two.getX(), two.getY(), pen);
        scene->addLine(two.getX(), two.getY(), three.getX(), three.getY(), pen);
        scene->addLine(three.getX(), three.getY(), one.getX(), one.getY(), pen);

        QGraphicsView *view = new QGraphicsView;
        view->setScene(scene);
        view->show();
    }

    void move(double x, double y) override
    {
        Point firstCenter = getMainCenter();
        Point diff(x - firstCenter.getX(), y - firstCenter.getY());
        one.setX(one.getX() + diff.getX());
        one.setY(one.getY() + diff.getY());
        two.setX(two.getX() + diff.getX());
        two.setY(two.getY() + diff.getY());
        three.setX(three.getX() + diff.getX());
        three.setY(three.getY() + diff.getY());
        setMainCenter(x, y);
    }

    void turn(double deg) override
    {
        Point firstCenter = getMainCenter();
        one.setY((one.getY() - one.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
        one.setX((one.getX() + one.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
        two.setY((two.getY() - two.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
        two.setX((two.getX() + two.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
        three.setY((three.getY() - three.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
        three.setX((three.getX() + three.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
        setCenter();
        move(firstCenter.getX(), firstCenter.getY());
    }

    void scale(double coeff) override
    {
        Point firstCenter = getMainCenter();
        Point sizeOneTwo(two.getX() - one.getX(), two.getY() - one.getY());
        Point sizeOneThree(three.getX() - one.getX(), three.getY() - one.getY());
        sizeOneTwo.setPoint(coeff * sizeOneTwo.getX(), coeff * sizeOneTwo.getY());
        sizeOneThree.setPoint(coeff * sizeOneThree.getX(), coeff * sizeOneThree.getY());
        two.setX(one.getX() + sizeOneTwo.getX());
        two.setY(one.getY() + sizeOneTwo.getY());
        three.setX(one.getX() + sizeOneThree.getX());
        three.setY(one.getY() + sizeOneThree.getY());

        setCenter();
        move(firstCenter.getX(), firstCenter.getY());
    }

    std::ostream& printShape(std::ostream &out, Shape &shape) override
    {
        rgb clr = shape.getShapeColor();
        out << "Triangle: (" << one.getX() << ", " << one.getY() << ") (" << two.getX() << ", " << two.getY() << ") (" << three.getX() << ", " << three.getY() << ")\n";
        out << "          ID: " << shape.getId() << " Color: (" << clr.getRed() << ", " << clr.getGreen() << ", " << clr.getBlue() << ")\n";
        return out;
    }
};


class Ellipse : public Shape
{
private:
    Point f1;
    Point f2;
    double height;
    double width;

public:
    Ellipse(){}
    Ellipse(rgb color, double x, double y, double height, double width) : Shape(color)
    {
        this->height = height;
        this->width = width;
        setMainCenter(x, y);
        double c = sqrt(width>height ? width*width/4 - height*height/4 : height*height/4 - width*width/4);
        f1.setY(height/2);
        f1.setX(x - c);
        f2.setY(height/2);
        f2.setX(x + c);
    }

    void show() override
    {
        QGraphicsScene *scene = new QGraphicsScene;
        scene->setSceneRect(-500, -500, 1000, 1000);

        rgb clr = getShapeColor();
        QColor color(clr.getRed(), clr.getGreen(), clr.getBlue());
        QPen pen;
        pen.setColor(color);
        pen.setWidth(3);

        Point centralPoint = getMainCenter();
        scene->addEllipse(centralPoint.getX() - width/2, centralPoint.getY() - height/2, width, height, pen);

        QGraphicsView *view = new QGraphicsView;
        view->setScene(scene);
        view->show();
    }

    void move(double x, double y) override
    {
        Point firstCenter = getMainCenter();
        Point diff(x - firstCenter.getX(), y - firstCenter.getY());
        f1.setX(f1.getX() + diff.getX());
        f1.setY(f1.getY() + diff.getY());
        f2.setX(f2.getX() + diff.getX());
        f2.setY(f2.getY() + diff.getY());
        setMainCenter(x,y);
        show();
    }

    void turn(double deg) override
    {
        f1.setY((f1.getY() - f1.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
        f1.setX((f1.getX() + f1.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
        f2.setY((f2.getY() - f2.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
        f2.setX((f2.getX() + f2.getY()*sin(deg*PI/180)) / cos(deg*PI/180));

        QGraphicsScene *scene = new QGraphicsScene;
        scene->setSceneRect(-500, -500, 1000, 1000);

        rgb clr = getShapeColor();
        QColor color(clr.getRed(), clr.getGreen(), clr.getBlue());
        QPen pen;
        pen.setColor(color);
        pen.setWidth(3);

        Point cet = getMainCenter();
        scene->addEllipse(cet.getX(), cet.getY(), width, height, pen);

        QGraphicsView *view = new QGraphicsView;
        view->setScene(scene);
        view->rotate(360-deg);
        view->show();
    }

    void scale(double coeff) override
    {
        height *= coeff;
        width *= coeff;
        Point centr = getMainCenter();
        double c = sqrt(width>height ? width*width/4 - height*height/4 : height*height/4 - width*width/4);
        f1.setY(height/2);
        f1.setX(centr.getX() - c);
        f2.setY(height/2);
        f2.setX(centr.getX() + c);
        show();
    }

    std::ostream& printShape(std::ostream &out, Shape &shape) override
    {
        rgb clr = shape.getShapeColor();
        out << "Ellipse: width = " << width << ", height = " << height << ", focus1(" << f1.getX() << ", " << f1.getY() << "), focus2(" << f2.getX() << ", " << f2.getY() << ")\n";
        out << "         ID: " << shape.getId() << " Color: (" << clr.getRed() << ", " << clr.getGreen() << ", " << clr.getBlue() << ")\n";
        return out;
    }
};


class RightTriangle : public Triangle
{
private:
    double side1;
    double side2;

public:
    RightTriangle(){}
    RightTriangle(rgb color, double x, double y, double side1, double side2)
    {
        this->side1 = side1;    //вертикаль
        this->side2 = side2;    //горизонталь
        setMainCenter(x, y);
        one.setPoint(x-side2/4, y-side1/4);
        two.setPoint(one.getX(), one.getY() + 3*side1/4);     //вертикаль
        three.setPoint(one.getX() + 3*side2/4, one.getY());   //горизонталь
        this->color.setColor(color.getRed(), color.getGreen(), color.getBlue());
    }

    std::ostream& printShape(std::ostream &out, Shape &shape) override
    {
        rgb clr = shape.getShapeColor();
        out << "RightTriangle: (" << one.getX() << ", " << one.getY() << ") (" << two.getX() << ", " << two.getY() << ") (" << three.getX() << ", " << three.getY() << ")\n";
        out << "               ID: " << shape.getId() << " Color: (" << clr.getRed() << ", " << clr.getGreen() << ", " << clr.getBlue() << ")\n";
        return out;
    }
};

#endif // SHAPE_H
