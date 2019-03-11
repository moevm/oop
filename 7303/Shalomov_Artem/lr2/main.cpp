#include <iostream>
#include <cmath>
#define toRadian(x) x*6.28/360
using namespace std;
inline int sign(float x){
	if(x==0)return 0;
	return (x>0)?1:-1;
}
class Shape{
protected:
    int id;
    float x, y;
    float angle = 0;
    float scaleFactor = 1;
    struct Color{
        unsigned char r,g,b;
    } color;
    virtual void print(ostream &out){}
    Shape(float centerX, float centerY)
        : x(centerX)
        , y(centerY){
		static int ID_COUNTER = 1;
        id = ID_COUNTER++;
	}
public:

    void moveTo(float centerX, float centerY){
        x = centerX;
        y = centerY;
    }
    void setRotation(float degrees){
        this->angle = degrees;
    }
    void scale(float scaleFactor){
        if(scaleFactor==0 || isnan(scaleFactor) || isinf(scaleFactor)) return;
        this->scaleFactor *= scaleFactor;
    }
    Color getColor(){ return color;}
    void setColor(Color color){
        this->color = color;
    }
    int getId(){return id;}

    friend ostream& operator<<(ostream &out,Shape &shape){
        shape.print(out);
        return out;
    }
};
class Rectangle : public Shape {
protected:
    float width, height;
    void print(ostream &out){
		out << "id: " << id  <<", Rectangle " << width*scaleFactor << "X" << height*scaleFactor << " with center in (" << x << "; " << y << ") ";
        out << "colored 0x" << std::hex
        << ((color.r&(unsigned char)0xf0)>>4) << (color.r&(unsigned char)0x0f)
        << ((color.g&(unsigned char)0xf0)>>4) << (color.g&(unsigned char)0x0f)
        << ((color.b&(unsigned char)0xf0)>>4) << (color.b&(unsigned char)0x0f);
        if(angle!=0) out << "  rotated on " << angle << " degrees (clockwise)";
		out << "\nvertices:\n";
		for(int i = 0; i < 4; i++)
			out << '(' << x - sign(cos(0.785+i*1.57))*(cos(toRadian(angle))*width - sin(toRadian(angle))*height)*scaleFactor/2
			<< "; " << y + sign(sin(0.785+i*1.57))*(sin(toRadian(angle))*width + cos(toRadian(angle))*height)*scaleFactor/2 << ")\n";
    }
public:
    Rectangle(float centerX, float centerY, float width, float height)
        : Shape(centerX, centerY){
        scaleFactor = sqrt(width*width + height*height);
        this->width = width/scaleFactor;
        this->height = height/scaleFactor;
    }
};
class Parallelogram : public Rectangle{
protected:
    float theta;
    void print(ostream &out){
        out << "id: " << id  <<", Parallelogram " << width*scaleFactor << "X" << height*scaleFactor << " theta: " << theta<< " with center in (" << x << "; " << y << ") ";
        out << "colored 0x" << std::hex
        << ((color.r&(unsigned char)0xf0)>>4) << (color.r&(unsigned char)0x0f)
        << ((color.g&(unsigned char)0xf0)>>4) << (color.g&(unsigned char)0x0f)
        << ((color.b&(unsigned char)0xf0)>>4) << (color.b&(unsigned char)0x0f);
        if(angle!=0) out << "  rotated on " << angle << " degrees (clockwise)";
		out << "\nvertices:\n";
		for(int i = 0; i < 4; i++)
			out << '(' << x -
			sign(cos(0.785+i*1.57))*(cos(toRadian(angle))*scaleFactor/2*(width-sign(tan(0.785+i*1.57))*height*(theta!=0?1/tan(toRadian(theta)):0))
			 - sin(toRadian(angle))*height*scaleFactor/2)
			<< "; " << y +
			sign(sin(0.785+i*1.57))*(sin(toRadian(angle))*scaleFactor/2*(width-sign(tan(0.785+i*1.57))*height*(theta!=0?1/tan(toRadian(theta)):0))
			 + cos(toRadian(angle))*height*scaleFactor/2) << ")\n";
    }
public:
    Parallelogram(float centerX, float centerY, float width, float height, float theta)
        : Rectangle(centerX, centerY, width, height)
        , theta(theta){}
};
class Hexagon : public Shape{
protected:
	void print(ostream &out){
		out << "id: " << id  <<", Hexagon inscribed in circle of radius " << scaleFactor << " with center in (" << x << "; " << y << ") ";
        out << "colored 0x" << std::hex
            << ((color.r&(unsigned char)0xf0)>>4) << (color.r&(unsigned char)0x0f)
            << ((color.g&(unsigned char)0xf0)>>4) << (color.g&(unsigned char)0x0f)
            << ((color.b&(unsigned char)0xf0)>>4) << (color.b&(unsigned char)0x0f);
        if(angle!=0) out << "  rotated on " << angle << " degrees (clockwise)";
		out << "\nvertices:\n";
		for(int i = 0; i < 6; i++)
            out << '(' << x + sin(1.0472*i+toRadian(angle))*scaleFactor << "; " << y + cos(1.0472*i + toRadian(angle))*scaleFactor << ")\n";
	}
public:
    Hexagon(float centerX,float centerY,float radius)
        : Shape(centerX, centerY){
        this->scaleFactor = radius;
    }

};

int main()
{
    Shape *b = new Rectangle(0,0,2,3), *c = new Parallelogram(0,0,10,10,30),*s = new Hexagon(0,0,10);
    s->setColor({0,0xff,10});
    cout << *c << *b << *s;
    delete s;
    delete c;
    delete b;
    return 0;
}
