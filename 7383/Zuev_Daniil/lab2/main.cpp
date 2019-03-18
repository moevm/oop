#include <iostream>
#include <cmath>

using namespace std;

double pi = 3.14;

class Shape
{
protected:
    //переменные a и b в разных фигурах отвечают за разное
    //в эллипсе и секторе эллипса это радиусы
    //в прямоугольнике это длины сторон
    double a;
    double b;
    //x и y - это координаты центра фигуры
    double x;
    double y;
    //angle - это угол между осью Oy и радиусом a в эллипсе,
    //направлением биссектрисы угла в секторе эллипса
    //стороной a в прямоугольнике
    double angle;
    unsigned short intensity_r;
    unsigned short intensity_g;
    unsigned short intensity_b;
public:
    Shape(double a, double b, double ang, double x1, double y1)
        :a(a > 0 ? a : 0), b(b > 0 ? b : 0)
        ,intensity_r(0),intensity_g(0),intensity_b(0)
    {
        x = x1;
        y = y1;
        int cl = ang/pi;
        angle = ang - cl*pi;
        if(angle < 0)
            angle += pi;
    }
    virtual ~Shape(){}
    void diplacement(double x1, double y1){
        x = x + x1;
        y = y + y1;
    }
    void rotate(double angle_r)
    {
        angle = angle + angle_r;
        int cl = angle/pi;
        angle = angle - cl*pi;
        if(angle < 0)
            angle += pi;
    }
    bool scale(double coeff)
    {
        if(coeff > 0)
        {
            a*=coeff;
            b*=coeff;
            return true;
        }
        return false;

    }
    void set_colour(unsigned short red,
                    unsigned short green,
                    unsigned short blue)
    {
        intensity_r = red;
        intensity_g = green;
        intensity_b = blue;
    }
    void get_colour(unsigned short& red,
                    unsigned short& green,
                    unsigned short& blue)
    {
        red = intensity_r;
        green = intensity_g;
        blue = intensity_b;
    }
    //virtual std::ostream& operator<< = 0;
};

class Ellips: public Shape
{
public:
    Ellips(double rad_a, double rad_b, double ang, double x1, double y1)
        :Shape(rad_a, rad_b, ang, x1, y1){}
    ~Ellips(){}
    friend std::ostream& operator<< (std::ostream &out, Ellips &ellips)
    {
        out << "Радиусы a и b эллипса равны " << ellips.a << " и " << ellips.b <<
               ",\n центр эллипса находится в точке с координатами " <<
               "( " << ellips.x << ", " << ellips.y << ")"<<
               ",\n угол между радиусом a и осью Oy равен " << ellips.angle <<
               ",\n цвета:\n" << "red = " <<ellips.intensity_r << endl <<
               "blue = " << ellips.intensity_g << endl <<
               "green = " << ellips.intensity_g << endl;

        return out;
    }
};

class Sector: public Ellips
{
private:
    double def_angle;//угол между биссектрисой сектора эллипса и радиусом a
    double angle_bet_rad;//угол между радиусами сектора
public:
    Sector(double rad_a, double rad_b, double ang,
           double x1, double y1, double ang_b_r, double ang_d)
        :Ellips(rad_a, rad_b, ang, x1, y1)
    {
        int cl = ang_b_r/(2*pi);
        angle_bet_rad = ang_b_r - cl*2*pi;
        if(angle_bet_rad < 0)
            angle_bet_rad += 2*pi;
        cl = ang_d/pi;
        def_angle = ang_d - cl*pi;
        if(def_angle < 0)
            def_angle += pi;
    }
    ~Sector(){}
    friend std::ostream& operator<< (std::ostream &out, Sector &sector)
    {
        out << "Радиусы a и b сектора равны " << sector.a << " и " << sector.b << ", " <<
               ",\n центр сектора находится в точке с координатами " <<
               "( " << sector.x << ", " << sector.y << ")"<<
               ",\n угол между радиусом a и осью Oy равен " << sector.angle <<
               ",\n угол между биссектрисой сектора эллипса и радиусом a равен " << sector.def_angle <<
               ",\n угол между радиусами сектора равен " << sector.angle_bet_rad <<
               ",\n цвета:\n" << "red = " <<sector.intensity_r << endl <<
               "blue = " << sector.intensity_g << endl <<
               "green = " << sector.intensity_g << endl;

        return out;
    }
};

class Rectangle: public Shape
{
public:
    Rectangle(double a, double b, double ang, double x1, double y1)
        :Shape(a, b, ang, x1, y1){}
    ~Rectangle(){}
    friend std::ostream& operator<< (std::ostream &out, Rectangle &rec)
    {
        out << "Стороны a и b прямоугольника равны " << rec.a << " и " << rec.b << ", " <<
               ",\n центр прямоугольника находится в точке с координатами " <<
               "( " << rec.x << ", " << rec.y << ")"<<
               ",\n угол между стороной a и осью Oy равен " << rec.angle <<
               ",\n цвета:\n" << "red = " <<rec.intensity_r << endl <<
               "blue = " << rec.intensity_g << endl <<
               "green = " << rec.intensity_g << endl;
        return out;
    }
};

int main()
{
    Sector s(1,2,6,3,4,3,7);//классы эллипса и прямоугольника ведут себя аналогично
    cout<<s;//до установления цветов
    s.set_colour(255,255,255);
    cout<<s;//после установления цветов
}
