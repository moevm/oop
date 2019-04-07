#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;
static int count = 0;

struct Point{
    double x;
    double y;
    Point(): x(0), y(0) {}
    Point(double _x, double _y): x(_x), y(_y) {}
};

struct Color{
    unsigned red;
    unsigned green;
    unsigned blue;
    Color(): red(0), green(0), blue(0) {}
    Color(unsigned r, unsigned g, unsigned b) : red(r), green(g), blue(b) {}
};

class Shape{
protected:
    int id;
    double angle;
    Color color;
    Point center;
    vector <Point> points;
    vector <double> sides;
public:
    Shape(): id(count), angle(0), color(), center(){
        count++;
    }
    Shape(int id, double _angle, Color _color, Point _point): id(count), angle(_angle), color(_color), center(_point){
        count++;
    }
    double get_angle(){
        return angle;
    }
    Point get_cntr(){
        return center;
    }
    int get_id(){
        return id;
    }
    Color get_color(){
        return color;
    }
    void set_color(unsigned r, unsigned g, unsigned b){
        color.red = r;
        color.green = g;
        color.blue = b;
    }
    void set_cntr(double absc, double ord){
        center.x = absc;
        center.y = ord;
    }
    virtual ~Shape(){
        points.clear();
        sides.clear();
        id--;
    }
    void move(const Point p){
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        center.x += dx;
        center.y += dy;
        for(auto &pnt : points){
            pnt.x += dx;
            pnt.y += dy;
        }
    }
    void rotate(int _angle){
        angle += _angle;
        _angle %= 360;
        double angle = _angle * M_PI / 180.0;
        for(size_t i = 0; i < points.size(); i++){
            double x = center.x + (points[i].x - center.x) * cos(angle) - (points[i].y - center.y) * sin(angle);
            double y = center.y + (points[i].x - center.x) * sin(angle) + (points[i].y - center.y) * cos(angle);
            points[i].x = x;
            points[i].y = y;
        }
    }
    void scale(double coefficient){
        double x;
        double y;
        for(size_t i = 0; i < points.size(); i++){
            x = center.x + (points[i].x - center.x) * coefficient;
            y = center.y + (points[i].y - center.y) * coefficient;
            points[i].x = x;
            points[i].y = y;
        }
    }
    friend ostream &operator<<(ostream &out, Shape *shape);
    virtual void print(ostream &out) = 0;
    virtual double area() = 0;
    virtual void sides_of_shape() = 0;
};

ostream &operator<<(ostream &out, Shape *shape){
    out << setw(45) << right  << "!Информация о фигуре!" << endl;
    out << "Центр фигуры: " << "(" << shape->get_cntr().x << ";" << shape->get_cntr().y << ")" << endl;
    out << "Цвет фигуры:: " << "(" << shape->get_color().red << "," << shape->get_color().green << "," << shape->get_color().blue << ")" << endl;
    out << "Угол: " << shape->get_angle() << endl;
    out << "Id фигуры: " << shape->get_id() << endl;
    out << "Площадь: " << shape->area() << endl;
    shape->print(out);
    out << "____________________________________" << endl;
    return out;
}

class Rhombus : public Shape{
public:
    Rhombus(const Point center, double dx, double dy, const Color _color) : Shape(count, 0, _color, Point(center)){
        id++;
        points.clear();
        Point A = Point(center.x + dx, center.y);
        Point B = Point(center.x, center.y + dy);
        Point C = Point(center.x - dx, center.y);
        Point D = Point(center.x, center.y - dy);
        points.push_back(A);
        points.push_back(B);
        points.push_back(C);
        points.push_back(D);
    }
    double area()override{
        double dx = points[0].x - points[1].x;
        double dy = points[1].y - points[0].y;
        double d1 = 2 * dx;
        double d2 = 2 * dy;
        double area = d1 * d2 / 2;
        return abs(area);
    }
    void sides_of_shape() override{
        sides.clear();
        double a = sqrt(pow((points[0].x - points[1].x), 2.0) + pow((points[0].y - points[1].y), 2.0));
        double b = a, c = a, d = a;
        sides.push_back(a);
        sides.push_back(b);
        sides.push_back(c);
        sides.push_back(d);
    }
    void print(ostream &out) override{
        sides_of_shape();
        out << "Все стороны фигуры равны: " ;
        out << sides[0] << endl;
        out << "Координаты фигуры: " ;
        for(int i = 0; i < points.size(); i++){
            out << i << ": (" << points[i].x << "; " << points[i].y << "); ";
        }
        out << endl;
    }
    ~Rhombus(){}
};

class Trapezium : public Shape{
public:
    Trapezium(const Point A, const Point B, double x1, double x2, const Color _color) : Shape(count, 0, _color, Point((A.x + B.x + x1 + x2) / 4, (2 * (A.y + B.y)) / 4)){
        id++;
        points.clear();
        Point D = Point(x1, A.y);
        Point C = Point(x2, B.y);
        points.push_back(A);
        points.push_back(B);
        points.push_back(C);
        points.push_back(D);
    }
    void sides_of_shape() override{
        sides.clear();
        double a = sqrt(pow((points[0].x - points[1].x), 2.0) + pow((points[0].y - points[1].y), 2.0));
        double b = sqrt(pow((points[1].x - points[2].x), 2.0) + pow((points[1].y - points[2].y), 2.0));
        double c = sqrt(pow((points[2].x - points[3].x), 2.0) + pow((points[2].y - points[3].y), 2.0));
        double d = sqrt(pow((points[3].x - points[0].x), 2.0) + pow((points[3].y - points[0].y), 2.0));
        sides.push_back(a);
        sides.push_back(b);
        sides.push_back(c);
        sides.push_back(d);
    }
    double area()override{
        sides_of_shape();
        double a = sides[1];
        double b = sides[3];
        double h = points[0].y - points[1].y;
        double area = h * (a + b) / 2;
        return abs(area);
    }
    void print(ostream &out) override{
        sides_of_shape();
        out << "Основания: " << sides[1] << ", " << sides[3] << endl;
        out << "Боковые стороны: " << sides[0] << ", " << sides[2] << endl;
        out << "Координаты фигуры: " ;
        for(int i = 0; i < points.size(); i++){
            out << i << ": (" << points[i].x << "; " << points[i].y << "); ";
        }
        out << endl;
    }
    ~Trapezium(){
        sides.clear();
    }
};

class Circle : public Shape{
public:
    Circle(const Point center, double r, const Color _color) : Shape(count, 0, _color, Point(center)){
        id++;
        points.clear();
        Point A = Point(center.x, center.y + r);
        Point B = Point(center.x + r, center.y);
        Point C = Point(center.x, center.y - r);
        Point D = Point(center.x - r, center.y);
        points.push_back(A);
        points.push_back(B);
        points.push_back(C);
        points.push_back(D);
    }
    void sides_of_shape() override{
      sides.clear();
      double r = (points[0].y - points[1].y);
      sides.push_back(r);
    }
    double area()override{
        sides_of_shape();
        double area = M_PI * pow(sides[0], 2.0);
        return abs(area);
    }
    void print(ostream &out) override{
        sides_of_shape();
        out << "Радиус:  " << sides[0] << endl;
        out << "Координаты фигуры: " ;
        for(int i = 0; i < points.size(); i++){
            out << i << ": (" << points[i].x << "; " << points[i].y << "), ";
        }
        out << endl;

    }
    ~Circle(){}
};

int main(){
    setlocale(LC_ALL, "Russian");
    cout << "Ромб" << endl;
    Shape *test1 = new Rhombus({1, 1}, 4, 6, {0, 0, 1});
    cout << test1;
    cout << "Маштабирование ромба" << endl;
    test1->scale(4);
    cout << test1;
    cout << "Трапеция" << endl;
    Shape *test2 = new Trapezium({1, 1}, {2, 5}, 5, 3, {0, 1, 0});
    cout << test2;
    cout << "Маштабирование трапеции" << endl;
    test2->scale(6);
    cout << test2;
    cout << "Перемещение трапеции" << endl;
    test2->move({10, 12});
    cout << test2;
    cout << "Поворот трапеции" << endl;
    test2->rotate(60);
    cout << test2;
    cout << "Круг" << endl;
    Shape *test3 = new Circle({5, 7}, 3, {1, 0, 0});
    cout << test3;
    cout << "Перемещение круга" << endl;
    test3->move({10, 12});
    cout << test3;
    cout << "Маштабирование круга" << endl;
    test3->scale(8);
    cout << test3;
    return 0;
}
