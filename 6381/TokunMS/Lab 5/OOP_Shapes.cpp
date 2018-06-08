#include "OOP_Shapes.h"

using namespace std;

	Point::Point(float x_, float y_) : x(x_), y(y_) {};
	void Point::move(float x_, float y_)
	{
		x += x_;
		y += y_;
	}
	
	void Point::rotate(float alpha)
	{
	 	float x_ = x * cos(alpha) - y * sin(alpha);
	 	float y_ = x * sin(alpha) + y * cos(alpha);
	 	x = x_; y = y_;		
	}

	void Point::scale(Point point0, float k)
	{
		x = point0.x + abs(x - point0.x)*k;
		y = point0.y + abs(y - point0.y)*k;		
	}

 
	Shape::~Shape() {};
	
	ostream& operator<< (ostream& s, const Shape& shape_)
	{
		return shape_.put(s);
	}

	Shape::Shape() : color(0) {};

    bool Shape::GetX()
    {
        bool found = false;
        for (Point &point_ : point) if(point_.x < 5) found = true;
        return found;
    }

    bool Shape::GetY()
    {
        bool found = false;
        for (Point &point_ : point) if(point_.y < 5) found = true;
        return found;
    }

	void Shape::Move(float x_, float y_)
	{
		for (Point &point_ : point) point_.move(x_, y_);
	}

	void Shape::Rotate(float alpha)
	{
		for (Point &point_ : point) point_.rotate(alpha);
	}

	void Shape::setColor(unsigned color_)
	{
		if (color_ > colors.size()) throw invalid_argument("It's not such color!");
		color = color_;
	}

	unsigned Shape::getColor() const
	{
		return color;
	}


	Ellipse::Ellipse(Point center, float r1_, float r2_) : r1(r1_), r2(r2_)
	{
		if ((r1_ <= 0) || (r2_ <= 0)) throw invalid_argument("Radius must be positive");
		point.push_back(center);	
	}	

	void Ellipse::Scale(float k) 
	{
		if (k <= 0) throw invalid_argument("Coefficient of scale must be positive");
		r1 *= k;
		r2 *= k;
	}
	
	float Ellipse::Perimeter() 
	{
		return (3.1416*r1*r2 + abs(r1-r2))/(r1 + r2);
	}
	ostream& Ellipse::put(ostream& out) const
	{
		out << "The figure is ellipse\nwith center in coordinates\n("
			<< point[0].x << "; " << point[0].y << ")\n"
			<< "and radius are r1 = " << r1 << "   r2 = " << r2 << "\n"
			<< "color is " << colors[getColor()] << "\n\n";
		return out;
	}
	
	string Trapezium::FriendlyName() const
	{
		return " ";
	}

	Trapezium::Trapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_) : topBase(abs(topBase_)), bottomBase(abs(bottomBase_))
	{
		if ((topLeftCoord.x == bottomLeftCoord.x) && (topLeftCoord.y == bottomLeftCoord.y)) throw invalid_argument("There is not distance between coordinates of left side of trapezium");
		if ((topBase_ <= 0) || (bottomBase_ <= 0)) throw invalid_argument("Bases of trapezium must be positive");
		
		point.push_back(topLeftCoord);
		point.push_back(bottomLeftCoord);
		point.push_back(Point(topLeftCoord.x + topBase, topLeftCoord.y));
		point.push_back(Point(bottomLeftCoord.x + bottomBase, bottomLeftCoord.y));
    }

	void Trapezium::Scale(float k)   
	{
		if (k <= 0) throw invalid_argument("Coefficient of scale must be positive");
		for (int i = 1; i < point.size(); i++) point[i].scale(point[0], k);
		topBase *= k; bottomBase *= k;
	}

	float Trapezium::Distance(Point a, Point b)
	{
		return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
	}

	float Trapezium::Perimeter()
	{
		float p = 0;
		for (int i = 0; i < point.size() - 2; i++) p += Distance(point[i], point[i+1]);
		p += Distance(point[0], point[point.size()-1]);
		return p;
	}

	ostream& Trapezium::put(ostream& out) const
	{
		out << "The figure is" << FriendlyName() << "trapezium\nwith coordinates\n";
		for (int i = 0; i < point.size(); i++) out << "(" << point[i].x << "; " << point[i].y << ")\n";
		out << "length of basis are top_base = " << topBase << "   bottom_base = " << bottomBase
			<< "\ncolor is " << colors[getColor()] << "\n\n";
		return out;
	}

	string IsoscelesTrapezium::FriendlyName() const
	{
		return " isolated ";
	}
	
    IsoscelesTrapezium::IsoscelesTrapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_) : topBase(topBase_), bottomBase(bottomBase_)
	{
        topBase_ = abs(-2 * topLeftCoord.x + bottomBase + 2 * bottomLeftCoord.x);
		if ((topLeftCoord.x == bottomLeftCoord.x) && (topLeftCoord.y == bottomLeftCoord.y)) throw invalid_argument("There is not distance between coordinates of left side of isotrapezium");
		if ((topBase_ <= 0) || (bottomBase_ <= 0)) throw invalid_argument("Bases of isotrapezium must be positive");
		
		point.push_back(topLeftCoord);
		point.push_back(bottomLeftCoord);
		point.push_back(Point(topLeftCoord.x + topBase, topLeftCoord.y));
		point.push_back(Point(bottomLeftCoord.x + bottomBase, bottomLeftCoord.y));
	}

    ostream& IsoscelesTrapezium::put(ostream& out) const
	{
		out << "The figure is" << FriendlyName() << "trapezium\nwith coordinates\n";
		for (int i = 0; i < point.size(); i++) out << "(" << point[i].x << "; " << point[i].y << ")\n";
		out << "length of basis are top_base = " << topBase << "   bottom_base = " << bottomBase
			<< "\ncolor is " << colors[getColor()] << "\n\n";
		return out;
	}
	
    void IsoscelesTrapezium::Scale(float k)   
	{
		if (k <= 0)
			throw invalid_argument("Coefficient of scale must be positive");
		for (int i = 1; i < point.size(); i++) point[i].scale(point[0], k);
		topBase *= k; bottomBase *= k;
	}

    float IsoscelesTrapezium::Distance(Point a, Point b)
	{
		return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
	}

    float IsoscelesTrapezium::Perimeter()
	{
		float p = 0;
		for (int i = 0; i < point.size() - 2; i++) p += Distance(point[i], point[i+1]);
		p += Distance(point[0], point[point.size()-1]);
		return p;
	}