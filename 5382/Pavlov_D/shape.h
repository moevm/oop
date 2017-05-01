#ifndef SHAPE_H
#define SHAPE_H
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
///////////////////////
/// Ôèãóğû
/// Êâàäğàò
/// Ïğÿìîóãîëüíûé òğåóãîëüíèê
/// Ğàâíîáåäğåííûé òğåóã.
///
///
/// Ñòğóêòóğà òî÷åê.
/////////////////

struct Point {
	std::vector<double  > xs;
	std::vector<double  > ys;
	int size;
	Point() :size(0) {}
};

struct line {
	std::vector<double  > xl1;
	std::vector<double  > yl1;
	std::vector<double  > xl2;
	std::vector<double  > yl2;
	std::vector<double  > k;
	std::vector<double  > b;
	std::vector<double  > d;
	//std::vector<double  > side;
	int size;
	line() :size(0) {}
	line(Point Array, std::vector<double  > inputsize) :size(Array.size)
	{
		/*
		std::cout << "CONST SIZE" << size << std::endl;
		for (int k = 0; k<size; k++) {
			std::cout << "x= " << Array.xs[k] << " " << "y= " << Array.ys[k] << std::endl;
		}
		for (int k = 0; k<size; k++) {
			std::cout << inputsize[k] << " ";
		}
		std::cout << std::endl;
		*/
		bool notSide = false;
		int c = 0;
		for (int q = 0; q<size; ++q)
		{
			for (int j = 1; j<(size - q); ++j)
			{
				//std::cout << q << " " << j << std::endl;
				double buffer = SizeSide(Array, q, q + j);
			//	std::cout << "SIDE " << buffer << std::endl;
				for (int n = 0; n<size; n++) {
					if (buffer == inputsize[n])
						break;
					if ((buffer != inputsize[n]) && (n == size - 1))
						notSide = true;
				}
				if (!notSide) {
					//std::cout << "!" << std::endl;
					//std::cout << "xs1= " << Array.xs[q] << " " << "ys1= " << Array.ys[q] << std::endl;
					//std::cout << "xs2= " << Array.xs[q + j] << " " << "ys2= " << Array.ys[q + j] << std::endl;
					double count1 = (Array.ys[q] - Array.ys[q + j]);
					//std::cout << "count1= " << count1 << std::endl;

					double count2 = (Array.xs[q] - Array.xs[q + j]);
					//std::cout << "count2= " << count2 << std::endl;
					// double buffer=((Array.ys[q]-Array.ys[q+j])/(Array.xs[q]-Array.xs[q+j]));
					//   double buffer=((Array.ys[q]-Array.ys[q+j])/(Array.xs[q]-Array.xs[q+j]));
					if (count1 == 0) {
						k.push_back(0);
						b.push_back(Array.xs[q]);
						d.push_back(1);
						xl1.push_back(Array.xs[q]);
						yl1.push_back(Array.ys[q]);
						xl2.push_back(Array.xs[q + j]);
						yl2.push_back(Array.ys[q + j]);
						c++;
					}
					if (count2 == 0) {
						k.push_back(-1);
						b.push_back(Array.xs[q]);
						d.push_back(0);
						xl1.push_back(Array.xs[q]);
						yl1.push_back(Array.ys[q]);
						xl2.push_back(Array.xs[q + j]);
						yl2.push_back(Array.ys[q + j]);
						c++;

					}
					if ((count1 != 0) && (count2 != 0))
					{
						double buffer = (double)count1 / count2;
						//   std::cout << "K= "<<buffer<<std::endl;
						k.push_back(buffer);
						d.push_back(1);
						buffer = Array.ys[q] - k[c] * Array.xs[q];
						//  std::cout << "b= "<<buffer<<std::endl;
						b.push_back(buffer);
						xl1.push_back(Array.xs[q]);
						yl1.push_back(Array.ys[q]);
						xl2.push_back(Array.xs[q + j]);
						yl2.push_back(Array.ys[q + j]);
						c++;
					}

				}
				notSide = false;

			}

		}
		//  for (int k=0;k<size;k++);


	}
private:
	double SizeSide(Point array, int pos1, int pos2)
	{
		return sqrt(pow(array.xs[pos1] - array.xs[pos2], 2.0) + pow(array.ys[pos1] - array.ys[pos2], 2.0));

	}

};
////////////////
class Shape
{
public:
	Shape() :colour_(0), pointCount_(0), ID_(0) {}
	Shape(Point array)
	{

		if (array.xs.size() != array.ys.size())
			throw std::invalid_argument("Not enought information ");
		if (!checkSame(array))
			throw std::invalid_argument("Shape have Equal points ");
		//std::vector<double  > side;
		//countSides(side,array);
	}

	virtual  ~Shape() {

	}

	unsigned int getColour() const;//âçÿòü öâåò
	void setColour(unsigned int colour); //ïîñòàâèòü öâåò
	void turn(double angle);  //ïîâåğíóòü
	void expand(int size); //ğàñøèğèòü
	void replaceShape(double mx, double my);//ïåğåñòàâèòü
	virtual void showShape(std::ostream& os) const = 0;  //ïîêàçàòü ôèãóğó
	int getPointCount() const;  //êîëè÷åñòâî òî÷åê
	int getID() const; //ÂÇßÒÜ ID ÔÈÃÓĞÛ
	int setNextID();//ÏÎÑÒÀÂÈÒÜ id ÍÎÂÎÉ
	friend std::ostream& operator<< (std::ostream& os, Shape& p); //ÔÓÍÊÖÈß ÄËß ÂÛÂÎÄÀ ÈÍÔÎĞÌÀÖÈÈ ×ÅĞÅÇ ÏÎÒÎÊ (ÍÅ ÁÛËÎ Â ÎĞÈÃÈÍÀËÅ)
	virtual void countSides(std::vector<double  > &side, Point array) = 0;
	bool similar(const Shape &sh1, const Shape &sh2);
	bool sameShape(const Shape &sh1) const;
	bool sameShape(Point &array) const;
	bool sameShape(Point &array, const Shape &sh1, const Shape &sh2) const;
	virtual  double area() = 0;
	bool itSide(double tside)
	{
		for (int count = 0; count<pointCount_; ++count) {
			if (tside == side[count])
				return true;
		}
		return false;
	}

	void findCenter(std::vector<double  > center);
protected:
	int  colour_; //ÖÂÅÒ
	int pointCount_; //êÎËÈ×ÅÑÒÂÎ ÒÎ×ÅÊ
	int ID_; //ID ÔÈÃÓĞÛ
	static int nextID_; //ÏÅĞÅÌÅÍÍÀß , ÊÎÒÎĞÀß ÑÒÀÂÈÒ id (ÑÌÎÒĞÈ , ×ÒÎ ÒÀÊÎÅ STATIC)

	Point point_;

	std::vector<double  > side;
	double area_;
	bool checkSame(Point array);
	void makePoint(Point array);
	bool insidePoint(double ix, double iy, const  Shape &shape) const;
	void cross(line lin1, int pos1, line lin2, int pos2, Point &pointer, const Shape &sh);

	//  bool similar();


};
int Shape::nextID_ = 0; //ÈÍÈÖÈÀËÈÇÀÖÈß ID
class Triangle : public Shape
{

public:
	Triangle() //:Shape()
	{

		colour_ = 0;
		pointCount_ = 3;
		ID_ = 0;
	}
	Triangle(Point array) :Shape(array)
	{


		pointCount_ = 3;
		if (array.size != pointCount_)
			throw std::invalid_argument("Not enought/Too much points ");
		// std::vector<double  > side;
		countSides(side, array);
		area_ = area();
		makePoint(array);
	}

	void showShape(std::ostream &os) const override
	{
		os << "I'm Triangle" << std::endl;
		for (int i = 0; i<pointCount_; ++i) {
			os << "POINT " << i + 1 << "(" << point_.xs[i] << ";" << point_.ys[i] << ")" << std::endl;
		}
	}
	double area() override {
		double per = 0;
		for (int count = 0; count<pointCount_; ++count)
			per += side[count];
		per = per / 2;
		return sqrt(per*(per - side[0])*(per - side[1])*(per - side[2]));


	}
	void countSides(std::vector<double  > & side, Point array) override
	{
		side.push_back(sqrt(pow(array.xs[0] - array.xs[1], 2.0) + pow(array.ys[0] - array.ys[1], 2.0)));//

		side.push_back(sqrt(pow(array.xs[0] - array.xs[2], 2.0) + pow(array.ys[0] - array.ys[2], 2.0)));//

		side.push_back(sqrt(pow(array.xs[1] - array.xs[2], 2.0) + pow(array.ys[1] - array.ys[2], 2.0)));//

	}

protected:


};
//int Triangle::pointCount_=3;

std::ostream& operator<< (std::ostream& os, Shape& p)
{
	p.showShape(os);
	return os;
}
///////////////////////////////////////

unsigned int Shape::getColour() const
{
	return colour_;
}
////////////////////////////////////

int Shape::getPointCount() const
{
	return pointCount_;
}
////////////////////////////////////
void Shape::setColour(unsigned int colour)
{
	colour_ = colour;
}
///////////////////////////////////
void Shape::findCenter(std::vector<double  >center)
{

	//Èñïîëüçóåòñÿ ìàòğèöà ïåğåâîğîòà .
	for (int i = 0; i<pointCount_; ++i) {
		center[0] += point_.xs[i];
		center[1] += point_.ys[i];
	}
	center[0] /= pointCount_;
	center[1] /= pointCount_;
}
bool Shape::checkSame(Point array) {

	for (int q = 0; q<array.size - 1; ++q) {
		for (int k = 1; k<array.size - q; ++k) {
			//  std::cout<<array.xs[q]<<" "<<array.ys[q]<< " and " <<array.xs[q+k]<< " "<<array.ys[q+k]<<std::endl;
			if ((array.xs[q] == array.xs[q + k]) && (array.ys[q] == array.ys[q + k])) {

				return false;
			}

		}
	}

	return true;
}

////////////////////////////////////
void Shape::turn(double angle)
{
	std::vector<double  > center = { 0,0 };
	findCenter(center);
	for (int i = 0; i<pointCount_; ++i) {
		point_.xs[i] = (point_.xs[i] - center[0])*cos(angle) - (point_.ys[i] - center[1])*sin(angle);
		point_.ys[i] = (point_.xs[i] - center[0])*sin(angle) + (point_.ys[i] - center[1])*cos(angle);
	}
}
////////////////////////////////////
void Shape::expand(int size)
{
	std::vector<double  > center = { 0,0 }; //x,y
	findCenter(center);
	for (int i = 0; i<pointCount_; ++i) {
		point_.xs[i] = (point_.xs[i] - center[0])*size + center[0];
		point_.ys[i] = (point_.ys[i] - center[1])*size + center[1];
	}
	for (int count = 0; count<pointCount_; ++count)
		side[count] = side[count] * size;
	area_ = area();
}

////////////////////////////////////
void Shape::replaceShape(double mx, double my)
{
	for (int i = 0; i<pointCount_; ++i) {
		point_.xs[i] = point_.xs[i] + mx;
		point_.ys[i] = point_.ys[i] + my;
	}
}
////////////////////////////////////
void Shape::makePoint(Point array)
{

	int count = array.size;
	if ((!point_.xs.empty()) && (!point_.ys.empty()))
	{

		point_.xs.clear();
		point_.ys.clear();
	}
	while (count != 0) {
		point_.xs.push_back(array.xs[count - 1]);
		point_.ys.push_back(array.ys[count - 1]);
		count--;
	}
	point_.size = array.size;


}
////////////////////////////////////
int Shape::getID() const
{
	return ID_;
}
////////////////////////////////////
int Shape::setNextID()
{
	nextID_++;
	return nextID_;
}
////////////////////////////////////

bool Shape::similar(const Shape &sh1, const Shape &sh2)
{
	//  std::cout<<"STEP1"<<std::endl;
	if (sameShape(sh1))
		return true;
	// std::cout<<"STEP2"<<std::endl;
	Point NewPoint;
	line lin1(sh1.point_, sh1.side);
	line lin2(sh2.point_, sh2.side);
	//for (int test = 0; test<sh1.pointCount_; test++)
	//{
		//std::cout << "lin1 d " << lin1.d[test] << " k " << lin1.k[test] << " b " << lin1.b[test] << std::endl;
	//}
	//for (int test = 0; test<sh2.pointCount_; test++)
//	{
	//	std::cout << "lin2 d " << lin2.d[test] << " k " << lin2.k[test] << " b " << lin2.b[test] << std::endl;
	//}
	// Point NewPoint();
	//  std::cout<<"STEP3"<<lin1.size<<lin2.size<<std::endl;
	for (int count = 0; count<sh1.pointCount_; count++) {

		if (!insidePoint(sh1.point_.xs[count], sh1.point_.ys[count], sh2)) {
			//   std::cout<<"notInside"<<std::endl;
			NewPoint.xs.push_back(sh1.point_.xs[count]);
			NewPoint.ys.push_back(sh1.point_.ys[count]);
			NewPoint.size++;
		}
	}
	//std::cout << "STEP4 " << NewPoint.size << std::endl;
	//for (int l = 0; l<NewPoint.size; l++)
	//	std::cout << NewPoint.xs[l] << " " << NewPoint.ys[l] << std::endl;
	if ((NewPoint.size>pointCount_) || (NewPoint.size == 0))
		return false;
	//std::cout << "STEP5" << std::endl;

	for (int count1 = 0; count1<lin1.size; count1++) {
		for (int count2 = 0; count2<lin2.size; count2++) {
			cross(lin1, count1, lin2, count2, NewPoint, sh1);

		}

	}

	//std::cout << "STEP6" << NewPoint.size << std::endl;
	for (int p = 0; p<NewPoint.size; p++)
		 // std::cout<<"NP "<< NewPoint.xs[p]<<" " << NewPoint.ys[p] << std::endl;
		if (NewPoint.size>pointCount_) {
			if (sameShape(NewPoint, sh1, sh2))
				return true;
			else return false;
		}

	// std::cout<<"STEP7"<<std::endl;
	if (sameShape(NewPoint))
		return true;
	else
		return false;
}
bool Shape::insidePoint(double ix, double iy, const Shape &shape) const
{

	for (int i = 0; i<pointCount_; ++i) {
		if ((shape.point_.xs[i] == ix) && (shape.point_.ys[i] == iy))
			return true;
	}

	double S = 0;
	Point buffer;
	buffer.size = 1;
	buffer.xs.push_back(ix);
	buffer.ys.push_back(iy);
	bool test = false;
	for (int count1 = 0; count1<shape.pointCount_; ++count1) {
		for (int count2 = 1; count2 + count1<shape.pointCount_; ++count2) {
			double tside = (sqrt(pow(shape.point_.xs[count1] - shape.point_.xs[count1 + count2], 2.0) + pow(shape.point_.ys[count1] - shape.point_.ys[count2 + count1], 2.0)));
			// std::cout<<"SIDE "<<tside<<std::endl;
			for (int count = 0; count<shape.pointCount_; ++count) {
				if (tside == shape.side[count])
					test = true;
			}

			if (test) {
				//    std::cout<<"WAS FOUND TRIANGLE"<<std::endl;
				buffer.xs.push_back(shape.point_.xs[count1]);
				buffer.ys.push_back(shape.point_.ys[count1]);
				buffer.size++;
				buffer.xs.push_back(shape.point_.xs[count1 + count2]);
				buffer.ys.push_back(shape.point_.ys[count1 + count2]);
				buffer.size++;

				// for (int p=0;p<buffer.size;++p)
				//      std::cout<<"TRIANGLE STUFF X "<<buffer.xs[p]<< " Y "<<buffer.ys[p]<<std::endl;
				//     std::cout<<"buffer size"<<buffer.size<<std::endl;
				Triangle triangle(buffer);

				S = S + triangle.area_;
				test = false;
				//triangle.~Shape();
				for (int i = buffer.size; i != 1; --i) {
					buffer.xs.pop_back();
					buffer.ys.pop_back();
					buffer.size--;
				}
				//    std::cout<<"AFTER"<<buffer.size<<std::endl;




			}
		}

	}

	if (S == shape.area_)
		return true;
	else
		return false;

}
bool Shape::sameShape(const Shape &sh1) const
{
	if (pointCount_ != sh1.pointCount_)
		return false;
	else
	{
		int count = 0;
		for (int i = 0; i<pointCount_; ++i) {
			for (int q = 1; q<pointCount_ - i; ++q) {
				if ((sh1.point_.xs[i] == point_.xs[i + q]) && (sh1.point_.ys[i] == point_.ys[i + q]))
					++count;
			}
		}
		if (count == pointCount_)
			return true;
		else
			return false;
	}
}
bool Shape::sameShape(Point &array) const
{
	if (pointCount_ != array.size)
		return false;
	else {
		int count = 0;
		for (int i = 0; i<pointCount_; ++i) {
			for (int q = 1; q<pointCount_ - i; ++q) {
				if ((array.xs[i] == point_.xs[i + q]) && (array.ys[i] == point_.ys[i + q]))
					++count;
			}
		}
		if (count == pointCount_)
			return true;
		else
			return false;

	}
}

bool Shape::sameShape(Point &array, const Shape &sh1, const Shape &sh2) const
{
	Point TroublePoint;
	int truecount = 0;
	for (int i = 0; i<array.size; i++)
	{
		bool check = false;
		for (int q = 0; q<pointCount_; q++) {
			if ((array.xs[i] == point_.xs[q]) && (array.ys[i] == point_.ys[q]))
			{
				check = true;
				truecount++;
			}
		}
		if (!check)
		{
			TroublePoint.size++;
			TroublePoint.xs.push_back(array.xs[i]);
			TroublePoint.ys.push_back(array.ys[i]);

		}
		check = false;


	}
	if (truecount != pointCount_)
		return false;
	int count = 0;
	for (int i = 0; i<TroublePoint.size; i++)
	{
		for (int q = 0; q<sh1.pointCount_; q++)
			if ((TroublePoint.xs[i] == sh1.point_.xs[q]) && (TroublePoint.ys[i] == sh1.point_.ys[q]))
				count++;


		for (int q = 0; q<sh2.pointCount_; q++)
			if ((TroublePoint.xs[i] == sh2.point_.xs[q]) && (TroublePoint.ys[i] == sh2.point_.ys[q]))
				count++;
		if (count == 0)
			return false;
		count = 0;

	}
	return true;


}

////////////////////////
void Shape::cross(line lin1, int pos1, line lin2, int pos2, Point &pointer, const Shape &sh)
{   // std::cout<<"LINE 1: d "<<lin1.d[pos1]<<" k "<<lin1.k[pos1] <<" b "<<lin1.b[pos1]<<std::endl;
	//  std::cout<<"LINE 2: d "<<lin2.d[pos2]<<" k "<<lin2.k[pos2] <<" b "<<lin2.b[pos2]<<std::endl;
	if ((lin1.d[pos1] == lin2.d[pos2]) && (lin1.b[pos1] != lin2.b[pos2]) && (lin1.k[pos1] == lin2.k[pos2]))
		// | | -no cross
		return;


	if ((lin1.d[pos1] == lin2.d[pos2]) && (lin1.k[pos1] == lin2.k[pos2]) && (lin1.b[pos1] == lin2.b[pos2])) {
		// same. no cross,but....
		//   bool pointinside1=insidePoint(lin1.xl1[pos1],lin1.yl1[pos1],lin2);
		//   bool pointinside2=insidePoint(lin1.xl2[pos1],lin1.yl2[pos1],lin2);
		//  if ( (pointinside1)&& (pointinside2)) {
		//      pointer.xs.push_back(crossX);
		//      pointer.ys.push_back(crossY);
		//      pointer.size++;
		return;
		//   }

	}
	double crossX;
	double crossY;
	//  if ((lin1.k[pos1]!=lin2.k[pos2]) && (lin1.b[pos1]!=lin2.b[pos2])) {
	if (lin2.d[pos2] == 0)
	{

		crossX = -lin2.b[pos2] / lin2.k[pos2];
		crossY = (lin1.k[pos1] * crossX + lin1.b[pos1]);



	}
	else {
		if ((lin2.d[pos2] * lin1.k[pos1] - lin2.k[pos2] * lin1.d[pos1]) == 0) {
			if (lin2.k[pos2] == 0) {
				crossY = lin2.b[pos2];
				crossX = (lin1.d[pos1] * crossY - lin1.b[pos1]) / lin1.k[pos1];
			}

			else {
				crossY = lin2.b[pos2] / lin2.d[pos2];
				crossX = (lin1.d[pos1] * crossY - lin1.b[pos1]) / lin1.k[pos1];
			}
		}
		else {

			// crossX=(-in1.b[pos1]+lin2.b[pos2])/(lin1.k[pos1]-lin2.k[pos2]);
			// crossY=(lin1.k[pos1]*crossX+lin1.b[pos1]);
			crossX = (lin2.b[pos2] * lin1.d[pos1] - lin2.d[pos2] * lin1.b[pos1]) / (lin2.d[pos2] * lin1.k[pos1] - lin2.k[pos2] * lin1.d[pos1]);
			crossY = (lin2.k[pos2] * crossX + lin2.b[pos2]) / lin2.d[pos2];

		}
	}
	//std::cout << "JOB  X " << crossX << " Y " << crossY << std::endl;
	bool check = false;
	for (int q = 0; q<pointer.size; q++)
	{
		if ((crossX == pointer.xs[q]) && (crossY == pointer.ys[q]))
			check = true;
	}
	if (!check)
	{
		bool step = false;
		for (int i = 0; i<sh.pointCount_; i++) {
			if ((sh.point_.xs[i] == crossX) && (sh.point_.ys[i] == crossY)) {
				pointer.xs.push_back(crossX);
				pointer.ys.push_back(crossY);
				pointer.size++;
			}
			step = true;
		}
		if (!step) {
			if (insidePoint(crossX, crossY, sh)) {
				pointer.xs.push_back(crossX);
				pointer.ys.push_back(crossY);
				pointer.size++;
			}
		}


	}
	return;
	//  }
}

#endif // SHAPE_H

