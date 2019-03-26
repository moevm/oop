#include <iostream>
#include <vector>
#include <math.h>
#include <cstddef> // size_t
using namespace std;

class Point{
public:
    Point(double x = 0, double y = 0): x(x), y(y){
    }
    double x;
    double y;
};

class Colour{
public:
    Colour(size_t r = 255, size_t g = 255, size_t b = 255)
        : r(r), g(g), b(b)
    {}
    size_t r;
    size_t g;
    size_t b;
};

class Shape{
public:
    Shape(Point center, Colour color)
        : center(center), color(color), angle(0.0) {
        static size_t i = 0;
        i++;
        id = i;
    }
    size_t getId(){
        return id;
    }
    double getAngle(){
        return angle;
    }
    double getCenterX(){
        return center.x;
    }
    double getCenterY(){
        return center.y;
    }
    void newColour(Colour color){
        this->color = color;
    }
    Colour getColour(){
        return color;
    }
    virtual void set_move(Point cntr) = 0;
    virtual void scaling(double k) = 0;
    virtual void rotating(double angl) = 0;
    virtual ostream& out_shape(ostream& stream, Shape& shape) = 0;
    friend ostream& operator << (ostream& stream, Shape& shape) {
        return shape.out_shape(stream, shape);
    }
protected:
    Point center;
    size_t id;
    Colour color;
    double angle;
};


class Circle : public Shape{
public:
    Circle(Point center, Colour color, double radius) : Shape(center, color){
        this->radius = radius;
        this->center = center;
        point.x = center.x + radius;
        point.y = center.y;

    }
    void set_move(Point center) override {
        double diff_x = center.x - this->center.x;
        double diff_y = center.y - this->center.y;
        point.x = point.x + diff_x;
        point.y = point.y + diff_y;
        this->center = center;
    }
    void scaling (double k) override {
        radius = radius * k;
        point.x = center.x + radius;
        point.y = center.y + radius;
    }
    void rotating(double angle) override {
        this->angle = this->angle + angle;
        if(this->angle >= 360.0){
            int k = this->angle / 360.0;
            this->angle = this->angle - 360.0 * k;
        }
        double radian = this->angle * M_PI / 180.0;
        double x = point.x - center.x;
        double y = point.y - center.y;
        point.x = x * cos(radian) - y * sin(radian) + center.x;
        point.y = x * sin(radian) + y * cos(radian) + center.y;
    }

    ostream& out_shape(ostream& stream, Shape& shape) override {
        stream << endl;
        stream << "Circle" << endl;
        stream << "ID: " << shape.getId() << endl;
        stream << "Colour: r = " << shape.getColour().r << ", g = " << shape.getColour().g << ", b = " << shape.getColour().b << endl;
        stream << "Center point: x = " << shape.getCenterX() << ", y = " << shape.getCenterY() << endl;
        stream << "Point: x = " << this->point.x << "; y = " << this->point.y << endl;
        stream << "Radius: " << this->radius << endl;
        stream << "Angle: " << shape.getAngle() << endl;
        stream << endl;
        return stream;
    }

private:
    double radius;
    Point point;

};
class Rhombus : public Shape{
public:
    Rhombus(Point center, Colour color, double diag_x, double diag_y) : Shape(center, color){
        this->diag_x = diag_x;
        this->diag_y = diag_y;
        this->center = center;
        vertix.push_back(Point(center.x + diag_x/2, center.y));
        vertix.push_back(Point(center.x, center.y + diag_y/2));
        vertix.push_back(Point(center.x - diag_x/2, center.y));
        vertix.push_back(Point(center.x, center.y - diag_y/2));

    }
    void rotating(double angle) override {
        this->angle = this->angle + angle;
        if(this->angle >= 360.0){
            int k = this->angle / 360.0;
            this->angle = this->angle - 360.0 * k;
        }
        double radian = this->angle * M_PI / 180.0;
        for(int i = 0; i < 4; i++){
            double x = vertix[i].x - center.x;
            double y = vertix[i].y - center.y;
            vertix[i].x = x * cos(radian) - y * sin(radian) + center.x;
            vertix[i].y = x * sin(radian) + y * cos(radian) + center.y;
        }
    }
    void scaling(double k) override{
        diag_x = diag_x * k;
        diag_y = diag_y * k;
        for(int i = 0; i < 4; i++){
            vertix[i].x = (vertix[i].x - center.x) * k + center.x;
            vertix[i].y = (vertix[i].y - center.y) * k + center.y;
        }
    }
    void set_move(Point new_cent) override {
        double diff_x = new_cent.x - this->center.x;
        double diff_y = new_cent.y - this->center.y;
        for(int i = 0; i < 4; i++){
            vertix[i].x = vertix[i].x + diff_x;
            vertix[i].y = vertix[i].y + diff_y;
        }
        this->center.x = new_cent.x;
        this->center.y = new_cent.y;
    }
    ostream& out_shape(ostream& stream, Shape& shape) override {
        stream << endl;
        stream << "Rhombus" << endl;
        stream << "ID: " << shape.getId() << endl;
        stream << "Angle: " << shape.getAngle() << endl;
        stream << "Colour: r = " << shape.getColour().r << ", g = " << shape.getColour().g << ", b = " << shape.getColour().b << endl;
        stream << "diag x: " << this->diag_x << "; diag y = " << this->diag_y << endl;
        stream << "Center point: x = " << shape.getCenterX() << ", y = " << shape.getCenterY() << endl;
        stream << "Coordinate:" << endl;
        for(int i = 0; i < 4; i++){
            stream << "x" << i+1 << " = " << vertix[i].x << ", y" << i+1 << " = " << vertix[i].y << endl;
        }
        stream << endl;
        return stream;
    }

private:
    double diag_x;
    double diag_y;
    vector <Point> vertix;
};
class Trapezium : public Shape{
public:
    Trapezium(Point center, Colour color, Point point1, Point point2, Point point3, Point point4) : Shape(center, color){

        if((point1.y != point2.y) || (point3.y != point4.y) ){
            throw string("It is not trapezium!");
        }
        else{
            this->vertix.push_back(Point(point1));
            this->vertix.push_back(Point(point2));
            this->vertix.push_back(Point(point3));
            this->vertix.push_back(Point(point4));
            this->center.x = 0.0;
            this->center.y = 0.0;
            if((center.x != 0) || (center.y != 0)){
                this->set_move(center);
            }
        }
    }
    void rotating(double angle) override {
        this->angle = this->angle + angle;
        if(this->angle >= 360.0){
            int k = this->angle / 360.0;
            this->angle = this->angle - 360.0 * k;
        }
        double radian = angle * M_PI / 180.0;
        for(unsigned int i = 0; i < vertix.size(); i++){
            double x = vertix[i].x - center.x;
            double y = vertix[i].y - center.y;
            vertix[i].x = x*cos(radian) - y * sin(radian) + center.x;
            vertix[i].y = x*cos(radian) + y * sin(radian) + center.y;
        }
    }
    void set_move(Point new_cent) override {
        double diff_x = new_cent.x - this->center.x;
        double diff_y = new_cent.y - this->center.y;
        for(int i = 0; i < 4; i++){
            vertix[i].x = vertix[i].x + diff_x;
            vertix[i].y = vertix[i].y + diff_y;
        }
        this->center.x = new_cent.x;
        this->center.y = new_cent.y;
    }
    void scaling(double k) override{
        for(int i = 0; i < 4; i++){
            vertix[i].x = (vertix[i].x - center.x) * k + center.x;
            vertix[i].y = (vertix[i].y - center.y) * k + center.y;
        }
    }
    ostream& out_shape(ostream& stream, Shape& shape) override {
        stream << endl;
        stream << "Trapezium" << endl;
        stream << "ID: " << shape.getId() << endl;
        stream << "Angle: " << shape.getAngle() << endl;
        stream << "Colour: r = " << shape.getColour().r << ", g = " << shape.getColour().g << ", b = " << shape.getColour().b << endl;
        stream << "Center point: x = " << shape.getCenterX() << ", y = " << shape.getCenterY() << endl;
        stream << "Coordinate:" << endl;
        for(int i = 0; i < 4; i++){
            stream << "x" << i+1 << " = " << vertix[i].x << ", y" << i+1 << " = " << vertix[i].y << endl;
        }
        stream << endl;
        return stream;
    }
private:
    vector <Point> vertix;
};

int main(){
    try{Trapezium trap1({0, 0}, {255, 234, 122}, {-3,-2}, {4, -2}, {1,2}, {-1,2});
        cout << trap1;
        trap1.set_move({1,1});
        cout << trap1;
    }catch(string &s){
        cout << s << endl;
    }
    Circle cir1({0, 0}, {255, 255, 255}, 5);
    cout << cir1;
    cir1.rotating(30);
    cout << cir1;
    Rhombus romb1({0, 0}, {100, 205, 225}, 4, 4);
    cout << romb1;
    romb1.newColour({105, 154, 145});
    romb1.scaling(2);
    cout << romb1;
    return 0;
}
