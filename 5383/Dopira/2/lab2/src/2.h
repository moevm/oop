#include <iostream>
#include <ostream>
struct  Point{
		int x;
		int y;
		Point(int _x, int _y): x(_x), y(_y){}
        bool operator == (const Point &p) const { return(x == p.x && y ==p.y); }
};
class Color{
	public:
		unsigned int red;
		unsigned int green;
		unsigned int blue;
		Color(unsigned int _red, unsigned int _green, unsigned int _blue):
			red(_red), green(_green), blue(_blue) {	}
        bool operator == (const Color &other) const
        {
            return (red == other.red &&
                    green == other.green &&
                    blue == other.blue);
        }
};
class Shape{
	private:
		static size_t counter;
		Color color;
	public:
		Shape(Color color) : color(color), id(counter++) {}//конструктор
 		virtual ~Shape(){} //деструктор
 		virtual void move(int dx, int dy)=0;//перемещение
		virtual void rotate(int angle)=0; //поворот на угол
 		virtual void scale(int k)=0;//масшабирование на коэффициент
        Color getColor() const;//раскраска
		void setColor(Color color);
 		friend std::ostream&operator<<(std::ostream& os, Shape& p);//поток вывода
 	protected:
		unsigned int id;
		virtual void print(std::ostream& os) = 0;
};
// Ellipse наследует Shape как public
class Ellipse : public Shape {
	protected:
		unsigned int a; //полуоси
		unsigned int b;
        unsigned int fi; //угол поворота
        Point center; //координаты центра
	public:   
		Ellipse(Color color, Point center, int a=0, int b=0, unsigned int fi=0) : Shape(color), a(a), b(b), fi(fi), center(center) {}//конструктор
		~Ellipse() {}//деструктор
 		void move(int dx, int dy) override;//перемещение
		void rotate(int angle) override; //поворот на угол
 		void scale(int k) override;//масшабирование на коэффициент
        Point getCenter() const;
 		unsigned int getAAxis();
 		unsigned int getBAxis();
 		unsigned int getAngle();
 	protected:
		void print(std::ostream& os) override;
};
//SectorOfEllipse наследует как Ellipse так и Parallelogram. 
//Тем не менее в SectorOfEllipse имеется только одна копия Shape! 
class SectorOfEllipse : public Ellipse {
	private:
		int f1;
		int f2;
	public:   
        SectorOfEllipse (Color color = Color(0, 0, 0), Point center = Point(0, 0), int a=0, int b=0, unsigned int fi=0, int f1 = 0, int f2 = 0) :
			Ellipse (color,center,a,b, fi), 
			f1(f1), 
			f2(f2) 
			{}//конструктор
		~SectorOfEllipse(){}//деструктор
		static void split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3);

        bool operator == (const SectorOfEllipse &other) const;
 	protected:
		void print(std::ostream& os) override;
};	
//Parallelogram наследует Shape как public
class Parallelogram : public Shape {
	private:
		Point a;
		Point b;
		Point c;
		Point d;
	public:   
		Parallelogram(Color color, Point a, Point b, Point c, Point d) : Shape (color), a(a), b(b), c(c), d(d) {}//конструктор
		~Parallelogram(){}//деструктор
		bool checkParallelogram(Point a, Point b, Point c, Point d);//проверка на параллелограмм
 		void move(int dx, int dy) override;//перемещение
		void rotate(int angle) override; //поворот на угол
 		void scale(int k) override;//масшабирование на коэффициент
 	protected:
		void print(std::ostream& os) override;
};
