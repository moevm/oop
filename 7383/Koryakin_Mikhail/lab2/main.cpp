#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point{
    double x;
    double y;
    Point(double x, double y): x(x),y(y){}
};
struct Colour{
    short r;
    short g;
    short b;
    Colour (short r, short g, short b):r(r),g(g),b(b){}
};

class Shape{
public:
    Shape(double x, double y):ang(0), cent(x,y), col(0,0,0){}

    void changePos(double x, double y){
        for(auto& it: pts){
            it.x+=x - cent.x;
            it.y+=y - cent.y;
        }
        cent.x=x;
        cent.y=y;
    }

    void forSize(double& k){
        if(k<0){
            k=fabs(k);
        }
        cent.x*=k;
        cent.y*=k;
        for(auto& it: pts){
            it.x*=k;
            it.y*=k;
        }
    }

    virtual void changeSize(double k)=0;

    void changeAngle(int deg){
        ang+=deg;
        ang%=360;
        double rad=ang*M_PI/180;
        for(auto& it: pts){
            double tmpx=it.x*cos(rad)-it.y*sin(rad);
            double tmpy=it.y*cos(rad)+it.x*sin(rad);
            it.x=tmpx;
            it.y=tmpy;
        }
    }

    void changeColour(short r, short g, short b){
        col={r,g,b};
    }

    void forPrint(ostream& out){
        out<<"Центр. коорд. "<<cent.x<<" "<<cent.y<<endl;
        out<<"Угол поворота "<<ang<<endl;
        out<<"Точки "<<endl;
        int count=0;
        for(const auto& it: pts){
            count++;
            out<<count<<") ("<<it.x<<", "<<it.y<<")\n";
        }
        out<<"Цвет "<<col.r<<" "<<col.g<<" "<<col.b<<endl;
    }

    virtual void print(ostream& out)=0;

    friend ostream& operator<<(ostream& out, Shape& sh){
        sh.forPrint(out);
        sh.print(out);
        return out;
    }
    virtual ~Shape(){}

protected:
    Point cent;
    int ang;
    Colour col;
    vector<Point> pts;
};

class Pentagon : public Shape{
public:
    Pentagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5):
    Shape((x1+x2+x3+x4+x5)/5,(y1+y2+y3+y4+y5)/5)
    {
        pts.push_back({x1,y1});
        pts.push_back({x2,y2});
        pts.push_back({x3,y3});
        pts.push_back({x4,y4});
        pts.push_back({x5,y5});
        /*for(int i=0; i<5;i++){
            perimeter+=sqrt(pow((pts[(i+1)%5].x - pts[i].x), 2) + pow((pts[(i+1)%5].y - pts[i].y), 2));
        }*/
    }

    void changeSize(double k){
        forSize(k);
    }

    void print(ostream& out){
        out<<"";
    }

};

class Trngl : public Shape{
public:
    Trngl(double x1, double y1, double x2, double y2, double x3, double y3) : Shape((x1+x2+x3)/3,(y1+y2+y3)/3), a(a), b(b), c(c) {
        pts.push_back({x1,y1});
        pts.push_back({x2,y2});
        pts.push_back({x3,y3});
        a = sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
        b = sqrt(pow(x3-x1, 2)+pow(y3-y1, 2));
        c = sqrt(pow(x3-x2, 2)+pow(y3-y2, 2));
    }

    void changeSize(double k){
        forSize(k);
        a*=k;
        b*=k;
        c*=k;

    }

    void print(ostream& out){
        out<<"Первая сторона "<< a<<"\n";
        out<<"Вторая сторона "<< b<<"\n";
        out<<"Третья сторона "<< c<<"\n";
    }

protected:
    double a;
    double b;
    double c;
};
class RightTrngl : public Trngl{
public:
    RightTrngl (double x1, double y1, double m, double n) :
    Trngl (x1, y1, x1+m, y1, x1, y1+n), a(a), b(b), c(c)  {
        /*pts.push_back({x1,y1});
        pts.push_back({x1+m,y1});
        pts.push_back({x1,y1+n});*/
        a = m;
        b = n;
        c = sqrt(pow(m,2)+pow(n,2));
    }

protected:
    double a;
    double b;
    double c;
};

int main(){

    cout<<"-----------\n";
    cout<<"RightTrngl\n";
    cout<<"-----------\n";
    RightTrngl r(0,0,2,1);
    cout<<r;

    cout<<"-----------\n";
    cout<<"Edited RightTrngl\n";
    cout<<"-----------\n";
    r.changeAngle(90);
    r.changeColour(5,77,133);
    r.changePos(4,5);
    r.changeSize(3);
    cout<<r;


    cout<<"-----------\n";
    cout<<"Pentagon\n";
    cout<<"-----------\n";
    Pentagon p(0,0,1,1,1,2,-1,2,-1,1);
    cout<<p;

    cout<<"-----------\n";
    cout<<"Edited Pentagon\n";
    cout<<"-----------\n";
    p.changeAngle(90);
    p.changeColour(5,77,133);
    p.changePos(4,4);
    p.changeSize(3);
    cout<<p;


    cout<<"-----------\n";
    cout<<"Triangle\n";
    cout<<"-----------\n";
    Trngl t(0,0,2,3,4,8);
    cout<<t;

    cout<<"-----------\n";
    cout<<"Edited Triangle\n";
    cout<<"-----------\n";
    t.changeAngle(90);
    t.changeColour(5,77,133);
    t.changePos(4,4);
    t.changeSize(-3);
    cout<<t;

    return 0;
}
