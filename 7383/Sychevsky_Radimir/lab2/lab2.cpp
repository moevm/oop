#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct Point
{
    int a;
    int b;
};

struct RGB
{
    int R;
    int G;
    int B;
};

class Shape
{
    protected:
        Point Centre;
        RGB Color;
        int Angle;
        double Scale;

    public:
        Shape(Point a = {0, 0}){
            Centre = {a.a, a.b};
            Color = {0, 0, 0};
            Scale = 1;
            Angle = 0;
        }
        virtual ~Shape(){}
        virtual void move_f(Point c){
            Centre.a = c.a;
            Centre.b = c.b;
        }
        void set_color(RGB new_color){
            Color.R = new_color.R;
            Color.G = new_color.G;
            Color.B = new_color.B;
        }
        void get_color(RGB &n_color){
            n_color.R = Color.R;
            n_color.G = Color.G;
            n_color.B = Color.B;
        }
        virtual void rotate(int f)
        {
            Angle += f;
            if(Angle > 360)
                Angle = Angle % 360;
        }
        virtual void scale(double m) = 0;
        friend std::ostream& operator<<(std::ostream& out, const Shape &s)
        {
            return out << "Centre: (" << s.Centre.a << ", " << s.Centre.b << ")" << std::endl;
        }
};

class Sector : public Shape
{
    protected:
        int Angle_two;
        int Radius;
    
    public:
        Sector(Point a, int radius, int angle_two) : Shape(a), Radius(radius), Angle_two(angle_two){}
        ~Sector(){}
        void rotate(int a) override
        {
            Angle += a;
            if(Angle > 360)
                Angle = Angle % 360;
            Angle_two += a;
            if(Angle_two > 360)
                Angle_two = Angle_two % 360;
        }
        void scale(double m) override
        {
            if(m != 0.0){
                Radius*=m;
            }
        }
        void change_angle_two(int a)
        {
            Angle_two += a;
            if(Angle_two > 360)
                Angle_two = Angle_two % 360;
        }
        friend std::ostream& operator<<(std::ostream& out, const Sector &s)
        {
            return out << "Centre: (" << s.Centre.a << ", " << s.Centre.b << ")" << std::endl
            << "Radius: " << s.Radius << endl
            << "Angle: " << s.Angle_two << endl;
        }
};

class Fivepointed_star : public Shape
{
    protected:
        int Radius;
        vector<Point> Arr;
    public:
        Fivepointed_star(Point a, int radius, vector<Point> &arr) : Shape(a), Radius(radius)
        {
            for(int i = 0; i < 5; i++)
                Arr.push_back(arr[i]);
        }
        ~Fivepointed_star(){}
        void move_f(Point a) override
        {
            int dx = Centre.a - a.a;
            int dy = Centre.b - a.b;
            for(int i = 0; i < 5; i++){
                Arr[i].a-=dx;
                Arr[i].b-=dy;
            }
            Centre.a = a.a;
            Centre.b = a.b;
        }
        void scale(double m) override
        {
            int dx;
            int dy;
            if(m != 0.0)
                for(int i = 0; i < 5; i++){
                    dx = Arr[i].a - Centre.a;
                    dy = Arr[i].b - Centre.b;
                    dx = dx * m;
                    dy = dy * m;
                    Arr[i].a = Centre.a + dx;
                    Arr[i].b = Centre.b + dy;
                }
        }
        friend std::ostream& operator<<(std::ostream& out, const Fivepointed_star &s)
        {
            return out << "Centre: (" << s.Centre.a << ", " << s.Centre.b << ")" << std::endl
            << "Radius: " << s.Radius << endl;
        }
};

class Ellipse : public Shape
{
    protected:
        int Radius_a;
        int Radius_b;
    public:
        Ellipse(Point a, int r_a, int r_b) : Shape(a), Radius_a(r_a), Radius_b(r_b){}
        ~Ellipse(){}
        void scale(double m) override
        {
            if(m != 0.0){
                Radius_a*=m;
                Radius_b*=m;
            }
        }
        friend std::ostream& operator<<(std::ostream& out, const Ellipse &s)
        {
            return out << "Centre: (" << s.Centre.a << ", " << s.Centre.b << ")" << std::endl
            << "Radius: " << s.Radius_a << ", " << s.Radius_b <<endl;
        }
};

int main(){

    return 0;
}