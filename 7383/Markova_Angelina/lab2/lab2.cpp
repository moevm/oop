#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

static int count = 0;      //глобальная внутренняя переменная

struct Point {             //структура координат
    double x, y;
    Point():x(0),y(0) {}   //конструктор по умолчанию, т.е если не инициализируем, то будет ноль
    Point(double curr_x, double curr_y):x(curr_x), y(curr_y) {} //если не нули, то передаём нужное значение
};

struct Color {             //структура цвета
    unsigned red;
    unsigned green;
    unsigned blue;
    Color(): red(0), green(0),blue(0) {}
    Color(unsigned r, unsigned g, unsigned b) : red(r), green(g), blue(b) {}
};

class Shape {              //класс фигура (любая)
public:

    Shape():id(count),angle(0), color(), center() {
        count++;
    }                      //конструктор по умолчанию, count всегда передаём, фигура изначально не повернута, и вызываем конструктор цвета и координат

    Shape(int id, double curr_angle, Color curr_color, Point curr_point):id(count), angle(curr_angle), color(curr_color), center(curr_point) {
        count++;           //конструктор по заданным значениям
    }

    double get_angle() {   //взятие угла фигуры (для печати используем)
        return angle;
    }

    Point get_center() {   //взятие координат центра фигуры
        return center;
    }

    int get_id() {         //взятие индивидуального адреса фигуры
        return id;
    }

    Color get_color() {    //взятие цвета фигуры
        return color;
    }

    void set_color(unsigned r,unsigned g,unsigned b){
        color.red = r;
        color.green = g;
        color.blue = b;
    }

    ~Shape() {
        points.clear();    //очищение массива вершин фигуры (вектор задается массивом структур)
        sides.clear();     //очищение сторон фигур (массив длин сторон)
        id--;
    }

    void move(const Point new_place) {       //смещение фигруры, относительно центра (перемещаем центр в новую точку)
        double dx = new_place.x - center.x;  //изменение координат
        double dy = new_place.y - center.y;
        center.x += dx;
        center.y += dy;
        for(auto& pnt : points) {            //смещение всех вершин
            pnt.x += dx;
            pnt.y += dy;
        }
    }

    void rotate(int curr_angle)              //поворот фигуры
    {
        angle = angle + curr_angle;          //к текущему повороту добавляем заданный угол (для вывода)
        curr_angle = curr_angle % 360;       //исключаем кол-во оборотов, берём остаток
        double rad = curr_angle*M_PI/180;    //перевод градусов в радианы
        double x, y; 
        for(auto& pnt : points) {            //для каждой точки
            x = pnt.x;                       //pnt - текущая координата
            y = pnt.y;
            pnt.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x; //матрица поворота
            pnt.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
        }

    }

    void scale(double multiplier) {          //масштабирование
        double x;
        double y;
        for(auto& pnt : points) {
            x = pnt.x; 
            y = pnt.y;
            pnt.x = center.x + (x - center.x) * multiplier;
            pnt.y = center.y + (y - center.y) * multiplier;
        }
    }

    virtual void print(ostream &out) = 0;    //определение вертуальной функции, поток вывода
    virtual void sides_of_shape() = 0;       //подсчет сторон
    virtual double area() = 0;               //площадь фигуры
    friend ostream& operator << (ostream &out, Shape* shape); //перегрузка оператора

protected:                                   //возможность изменения в наследниках
    double angle;
    int id;
    Point center;
    Color color;
    vector <Point> points;
    vector <double> sides;
};

ostream& operator << (ostream& out, Shape* shape) {
    out << "Данные о фигуре:"<<endl;
    out << "Координаты центра: " <<"("<< shape->get_center().x << ";" << shape->get_center().y << ")" << endl;
    out << "Цвет (RGB): " <<"("<< shape->get_color().red << ","<< shape->get_color().green << ","<< shape->get_color().blue << ")" << endl;
    out << "Угол поворота = " << shape->get_angle() << endl;
    out << "Id: " << shape->get_id() << endl;
    out << "Площадь = " << shape->area() << endl;
    shape->print(out);
    out << "---------------------------------------------------------------------"<<endl;
    return out;
}

class Square : public Shape {
public:
    Square(const Point A, const Point center, const Color curr_color) : Shape(count, 0, curr_color, Point(center)) { //?
        id++;
        points.clear();                      //очищаешь массив
        points.push_back(A);                 //левый верхний угол
        double dif = abs(A.x - center.x);
        points.push_back(Point(A.x + 2 * dif, A.y));             //B
        points.push_back(Point(A.x + 2 * dif, A.y - 2 * dif));   //C
        points.push_back(Point(A.x, A.y - 2 * dif));             //D по часовой
    }

    void sides_of_shape() override {         //защита от опечатки, т.е мы используем функцию из shape
        sides.clear();
        double a = 2*abs(points[0].x - center.x);
        sides.push_back(a);
    }

    double area() override {
        sides_of_shape();
        double area = pow(sides[0], 2.0);
        return area;
    }

    void print(ostream &out) override {
        out << "Сторона квадрата: " << sides[0] << endl;
        out << "Координаты вершин: ";
        for(int i = 0; i < points.size(); i++) {
            out << i << ": (" << points[i].x << "; " << points[i].y << ") || ";
        }
        out << endl;
    }

    ~Square() {}
};

class Pentagon : public Shape {
public:
    Pentagon(const Point center, const Point A, const Color curr_color) : Shape(count, 0, curr_color, Point(center)) {
        id++;
        points.clear();
        push_points(A);
    }

    void push_points(Point A) {
        points.push_back(A);
        int c = 0; //счетчик для цикла
        Point tmp; //временные координаты
        tmp.x = A.x;
        tmp.y = A.y;
        while (c < 4) {
            points.push_back(rotate_point(tmp, 72));
            c++;
        }
    }

    void sides_of_shape() override {
        sides.clear();
        double n = sqrt(pow((points[0].x - points[1].x), 2.0) + pow((points[0].y - points[1].y), 2.0));
        sides.push_back(n);
    }

    double area() override {
        sides_of_shape();
        double area = 5*pow(sides[0], 2.0)/(tan(M_PI/5)*4);
        return abs(area);
    }

    Point rotate_point(Point &P, int curr_angle) {
        double rad = curr_angle*M_PI/180;
        double x, y;
        x = P.x;
        y = P.y;
        P.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
        P.y = (x - center.x) * sin(rad) - (y - center.y) * cos(rad) + center.y;
        return P;
    }

    void print(ostream &out) override {
        int i = 0;
        out << "Сторона правильного пятиугольника: " << sides[0] << endl;
        out << "Координаты вершин: " ;
        for(int i = 0; i < points.size(); i++) {
            out << i << ": (" << points[i].x << "; " << points[i].y << ") || ";
        }
        out << endl;

    }

    ~Pentagon() {}
};

class Fivepointed_star: public Pentagon {
public:
    Fivepointed_star(const Point center, double radius_big, const Color curr_color) : Pentagon(Point(center), Point(center.x + radius_big, center.y), curr_color) {
        id++;
        points.clear();
        Point A = Point(center.x + radius_big, center.y);
        push_points(A);
        Point F = Point(center.x + (radius_big*cos(2*M_PI/5)/cos(M_PI/5)), center.y);
        rotate_point(F, 36);
        push_points(F);
    }

    void sides_of_shape() override {
        sides.clear();
        double n = sqrt(pow((points[0].x - points[5].x), 2.0) + pow((points[0].y - points[5].y), 2.0));
        sides.push_back(n);
    }

    double area() override {
        sides_of_shape();
        double AB = sides[0];
        double BC = abs(points[0].x - center.x)*cos(2*M_PI/5)/cos(M_PI/5); //соотношение радиусов вписанной и описанной окружностей
        double CA = abs(points[0].x - center.x);
        double p = (AB+BC+CA)/2;
        double area = 10 * sqrt(p*(p-AB)*(p-BC)*(p-CA));                   //по формуле Герона
        return area;
    }

    void print(ostream &out) override {
        int i, j = 0;
        out << "Сторона пятиконечной звезды: " << sides[0] << endl;
        out << "Координаты вершин: " ;
        for(i = 0; i < points.size() - 5; i++) {
            out << i << ": (" << points[i].x << "; " << points[i].y << ") || ";
        }
        out << endl;
        out << "Координаты пересечений: " ;
        for(j = 5; j < points.size(); j++) {
            out << j << ": (" << points[j].x << "; " << points[j].y << ") || ";
        }
        out << endl;
    }

    ~Fivepointed_star() {}
};

int main() {
    Shape* test1 = new Square ({0,6}, {3,3}, {0, 1, 0} );
    cout << test1;
    test1->rotate(90);
    cout << test1;
    Shape* test2 = new Pentagon ({0,0}, {0,8}, {0, 1, 0});
    cout << test2;
    test2->scale(3);
    cout << test2;
    Shape* test3 = new Fivepointed_star ({1,4}, 8, {0, 1, 0});
    cout << test3;
    test3->move({5, 10});
    cout << test3;
    return 0;
}
