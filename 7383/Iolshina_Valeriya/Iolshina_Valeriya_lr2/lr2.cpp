#include <iostream>
#include<cmath>

class Shape
{
protected:
	double x, y;
  int r, g, b;
  int id;
  static int next_id;

public:

	Shape(double new_x = 0, double new_y = 0, double new_angle = 0) : x(new_x), y(new_y), id(++next_id)
	{
    r = g = b = 0;
  }

	virtual ~Shape() {}

	void setColor(int new_r, int new_g, int new_b)
	{
    r = new_r;
    g = new_g;
    b = new_b;
  }

  void getColor(int &cur_r, int &cur_g, int&cur_b)
	{
    cur_r = r;
    cur_g = g;
    cur_b = b;
  }

	virtual void move(double x, double y) = 0;
  virtual void rotate(double angle) = 0;
  virtual void scale(double k) = 0;

  friend std::ostream & operator << (std::ostream &out, const Shape &figure)
	{
		out << "Координаты центра:" << figure.x << ", " << figure.y << std::endl;
    out << "ID: " << figure.id << std::endl;
    out << "Цвет: " << figure.r << ", " << figure.g << ", " << figure.b << std::endl;
		return out;
	}
};


int Shape::next_id = 0;

class Circle : public Shape
{
protected:
	double radius;

public:

	Circle(double new_x = 0, double new_y = 0, double _radius = 0) : Shape(new_x, new_y), radius(_radius) {}
	~Circle() {}

	void move(double new_x, double new_y)
	{
		x = new_x;
		y = new_y;
	}

  void scale(double k) override
	{
    radius *= k;
  }

	void rotate(double new_angle) override
	{}

  friend std::ostream & operator << (std::ostream &out, Circle &figure)
	{
    out << "\tКруг" << std::endl;
    out << (Shape&) figure << std::endl;
    out << "Радиус: " << figure.radius;
		return out;
	}

};

class CircleSeg : public Circle
{
protected:
	double x1, x2, y1, y2;  //координаты вершин
	double seg_angle;

public:

	CircleSeg(double angle = 0, double radius = 0, double new_x = 0, double new_y = 0)
        : Circle(new_x, new_y, radius), seg_angle(angle)
	{}

		void move(double new_x, double new_y)
		{
	    x = new_x;
	    y = new_y;
			double dx = abs(x - new_x);
			double dy = abs(y - new_y);
			x1 += dx;
			x2 += dx;
			y1 += dy;
			y2 += dy;
	  }

	void scale(double k) override
	{
		radius *= k;
	}

	void rotate(double new_angle) override
	{
		double X = x;
		x1 = x + (x - x1)*cos(new_angle) - (y - y1)*sin(new_angle);
		y1 = y + (y - y1)*cos(new_angle) - (x - x1)*sin(new_angle);
		x2 = x + (x - x2)*cos(new_angle) - (y - y2)*sin(new_angle);
		y2 = y + (y - y2)*cos(new_angle) - (x - x2)*sin(new_angle);
	}


	~CircleSeg() {}

        friend std::ostream & operator << (std::ostream &out, const CircleSeg &figure)
				{
            out << "\tСегмент" << std::endl;
            out << (Circle&) figure << std::endl;
            out << "Угол сегмента: " << figure.seg_angle << std::endl;
            return out;
	      }
};

class Trapeze : public Shape
{
    protected:
        double top_side;
        double bottom_side;
        double height;
        double x1, x2, x3, x4;
				double y1, y2, y3, y4;

    public:

    Trapeze(double top, double bottom, double _x1, double _y1, double _x2, double _y2, double new_x = 0, double new_y = 0)
     : Shape(new_x, new_y), top_side(top), bottom_side(bottom), x1(_x1), y1(_y1), x2(_x2), y2(_y2)
		 {
         height = abs(y2 - y1);
         y = (height/3) * ((2*top_side + bottom_side)/(top_side+bottom_side));
         x = x1 + bottom_side/2;
     }

     ~Trapeze() {}

		 void move(double new_x, double new_y)
	 	{
	 		x = new_x;
	 		y = new_y;
			double dx = abs(x - new_x);
			double dy = abs(y - new_y);
			x1 += dx;
			x2 += dx;
			y1 += dy;
			y2 += dy;
			x3 += dx;
			x4 += dx;
			y3 += dy;
			y4 += dy;
	 	}

     void scale(double k) override
		 {
			 top_side *= k;
			 bottom_side *= k;
			 height *= k;
			 x1 = x + (x1 - x)*k;
			 x2 = x + (x2 - x)*k;
			 y1 = y + (y1 - y)*k;
			 y2 = y + (y2 - y)*k;
		 }

		void rotate(double new_angle) override
 		{
 			double X = x;
 			x1 = x + (x - x1)*cos(new_angle) - (y - y1)*sin(new_angle);
 			y1 = y + (y - y1)*cos(new_angle) - (x - x1)*sin(new_angle);
 			x2 = x + (x - x2)*cos(new_angle) - (y - y2)*sin(new_angle);
 			y2 = y + (y - y2)*cos(new_angle) - (x - x2)*sin(new_angle);
 		}

    friend std::ostream & operator << (std::ostream &out, const Trapeze &figure)
        {
        out << "\tТрапеция" << std::endl;
        out << (Shape&) figure << std::endl;
        out << "Длины оснований: верхнее-" << figure.top_side << " нижнее-" << figure.bottom_side << std::endl;
        out << "Высота: " << figure.height << std::endl;
				out << "Координаты вершин: верхняя левая-" << figure.x1 << ", " << figure.y1 << " нижняя левая-" << figure.x2 << ", " << figure.y2 << std::endl;
        return out;
	}


};

int main()
{
    Circle A(7,5,20);
    CircleSeg B(15, 17);
    Trapeze C(14, 34, 17, 6, 8, 4);
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;
    A.rotate(33);
    A.scale(4);
    A.setColor(255, 128, 0);
    B.rotate(60);
    B.scale(2);
    B.setColor(15,15,15);
    B.move(2,4);
    C.rotate(25);
    C.scale(5);
    C.setColor(33,5,7);
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;
}
