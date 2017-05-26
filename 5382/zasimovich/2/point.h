#ifndef _POINT_
#define _POINT_
#include <cmath>
const double PI = 4*atan(1.0);
class Point
{
public:
		double X;double Y;
		Point(double x = 0, double y = 0)
		{X = x; Y = y;};

		double getX()
		{ return X;}
		double getY()
		{ return Y;}
		void setX(double x)
		{ X = x;}
		void setY(double y)
		{ Y = y;}
		friend Point Mahtabus(double& P, Point& point,Point& centre){//маштабирование в P раз точки point относительно центра
		     Point point1;
			 point1.setX (centre.getX()+(point.getX()-centre.getX() )* P );
             point1.setY (centre.getY()+(point.getY()-centre.getY() )* P );
		     return point1;
		}
		friend Point Movus(double& x,double& y, Point& point,Point& centre){//перемещение точки, анологичное перемещению центра
		    Point point1;
			point1.setX (point.getX() + x-centre.getX() );
	        point1.setY (point.getY()+ y-centre.getY());
		    return point1;
		
		}
		friend Point Turnus(double& angle, Point& point,Point& centre){//поворот точки относительно центра
			Point point1;
		    point1.setX (centre.getX()+(point.getX()-centre.getX())*cos((angle)*PI/180)-(point.getY()-centre.getY())*sin((angle)*PI/180));	
	        point1.setY (centre.getY() + (point.getX()-centre.getX())*sin((angle)*PI/180)+(point.getY()-centre.getY())*cos((angle)*PI/180));
		    return point1;
		}

		friend double Distance(Point& point,Point& centre){//поворот точки относительно центра
			
		    return sqrt(pow((point.getX()-centre.getX()),2)+pow((point.getY()-centre.getY() ),2));
		}



};

#endif