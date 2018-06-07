#include "shape.h"

	void Shape::setColor(string a){
		color = a;
	}
	string Shape::getColor(){
		return color;
	}
	void Circle:: printOUT(ostream& out){
		out << "center " << "(" << center.x << ";" << center.y << ")" << endl;
    	out << "right" << "(" << right.x << ";" << right.y << ")" << endl;
    	out << "top" << "(" << top.x << ";" << top.y << ")" << endl;
    	out << "left" << "(" << left.x << ";" << left.y << ")" << endl;
    	out << "bottom" << "(" << bottom.x << ";" << bottom.y << ")" << endl;
    	out << "color " << color << endl; 
	}
	void Circle:: info(){
		cout << "Circle " << square << ", " << color << endl;
	}
	double Circle:: getArea(){
		return square;
	}
	void Circle:: move(double x, double y) {
		double diffX, diffY;
		diffX = center.x - x;
		diffY = center.y - y;
		center = {x, y};
		right = {right.x - diffX, right.y - diffY};
		top = {top.x - diffX, top.y - diffY};
		left = {left.x - diffX, left.y - diffY};
		bottom = {bottom.x - diffX, bottom.y - diffY};
	}
	void Circle:: turn(int anglein){
		if (angle == 0){
			angle = anglein % 360;
		}
		else{
			angle = (angle + (anglein % 360)) % 360;
		}
		
		cout << angle << endl;
		right = 	{(center.x + radius*cos(angle*PI/180)), (center.y + radius*sin(angle*PI/180))};
		top = 		{(center.x - radius*sin((angle)*PI/180)), (center.y + radius*sin((90 - angle)*PI/180))};
		left = 		{(center.x - radius*cos(angle*PI/180)), (center.y - radius*sin(angle*PI/180))};
		bottom = 	{(center.x + radius*sin((angle)*PI/180)), (center.y - radius*sin((90 - angle)*PI/180))};
	}
	void Circle::scale(double coeff){
		radius = radius * coeff;
		cout << radius << endl;
		right = 	{(center.x + radius*cos(angle*PI/180)), (center.y + radius*sin(angle*PI/180))};
		top = 		{(center.x - radius*sin((angle)*PI/180)), (center.y + radius*sin((90 - angle)*PI/180))};
		left = 		{(center.x - radius*cos(angle*PI/180)), (center.y - radius*sin(angle*PI/180))};
		bottom = 	{(center.x + radius*sin((angle)*PI/180)), (center.y - radius*sin((90 - angle)*PI/180))};
	}


	void Rectangle::move(double x, double y) {
		double diffX, diffY;
		diffX = center.x - x;
		diffY = center.y - y;
		center = {x, y};
		rightT = {rightT.x - diffX, rightT.y - diffY};
		rightB = {rightB.x - diffX, rightB.y - diffY};
		leftT = {leftT.x - diffX, leftT.y - diffY};
		leftB = {leftB.x - diffX, leftB.y - diffY};
	}
	void Rectangle::info(){
		cout << "Rectangle " << square << ", " << color << endl;
	}
	double Rectangle::getArea(){
		return square;
	}
	void Rectangle::turn(int anglein){
		// НА СКОЛЬКО УМЕНЬШАЕШЬ НА СТОЛЬКО И УВЕЛИЧИВАЕШЬ С ПРОТИВОПОЛОЖНОЙ СТОРОНЫ!!!!!!
		if (angle == 0){
			angle = anglein % 360;
		}
		else{
			angle = (angle + (anglein % 360)) % 360;
		}
		rightT = 	{(center.x + dia*cos((angle + corner)*PI/180)), (center.y + dia*sin((angle + corner)*PI/180))};
		rightB = 	{(center.x + dia*cos((angle - corner)*PI/180)), (center.y - dia*sin((-angle + corner)*PI/180))};
		leftT = 	{(center.x - dia*cos((angle - corner)*PI/180)), (center.y + dia*sin((-angle + corner)*PI/180))};
		leftB = 	{(center.x - dia*cos((angle + corner)*PI/180)), (center.y - dia*sin((angle + corner)*PI/180))};
	}
	void Rectangle::scale(double coeff){
		dia *= coeff;
		rightT = 	{(center.x + dia*cos((angle + corner)*PI/180)), (center.y + dia*sin((angle + corner)*PI/180))};
		rightB = 	{(center.x + dia*cos((angle - corner)*PI/180)), (center.y - dia*sin((-angle + corner)*PI/180))};
		leftT = 	{(center.x - dia*cos((angle - corner)*PI/180)), (center.y + dia*sin((-angle + corner)*PI/180))};
		leftB = 	{(center.x - dia*cos((angle + corner)*PI/180)), (center.y - dia*sin((angle + corner)*PI/180))};
	}
	void Rectangle::printOUT(ostream& out){
		out << "center " << "(" << center.x << ";" << center.y << ")" << endl;
    	out << "right top" << "(" << rightT.x << ";" << rightT.y << ")" << endl;
    	out << "right bottom" << "(" << rightB.x << ";" << rightB.y << ")" << endl;
    	out << "left top" << "(" << leftT.x << ";" << leftT.y << ")" << endl;
    	out << "left bottom" << "(" << leftB.x << ";" << leftB.y << ")" << endl;
    	out << "color " << color << endl; 
	}



	void Trapeze::info(){
		cout << "Trapeze " << square << ", " << color << endl;
	}
	double Trapeze::getArea(){
		return square;
	}
	void Trapeze::move(double x, double y) {
		double diffX, diffY;
		diffX = center.x - x;
		diffY = center.y - y;
		center = {x, y};
		rightT = {rightT.x - diffX, rightT.y - diffY};
		rightB = {rightB.x - diffX, rightB.y - diffY};
		leftT = {leftT.x - diffX, leftT.y - diffY};
		leftB = {leftB.x - diffX, leftB.y - diffY};
	}
	void Trapeze::turn(int anglein){
		double s = 0;
		if (angle == 0){
			angle = anglein % 360;
		}
		else{
			angle = (angle + (anglein % 360)) % 360;
		}
		rightT = 	{round((center.x + dia*cos((angle + corner)*PI/180) - dif2*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((angle + corner)*PI/180) - dif2*sin(angle * PI / 180))*10)/10};
		rightB = 	{round((center.x + dia*cos((angle - corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((-angle + corner)*PI/180))*10)/10};
		leftT = 	{round((center.x - dia*cos((angle - corner)*PI/180) + dif1*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((-angle + corner)*PI/180) + dif1*sin(angle * PI / 180))*10)/10};
		leftB = 	{round((center.x - dia*cos((angle + corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((angle + corner)*PI/180))*10)/10};
	}
	void Trapeze::scale(double coeff){
		dia *= coeff;
		dif1 *= coeff;
		dif2 *= coeff;
		rightT = 	{round((center.x + dia*cos((angle + corner)*PI/180) - dif2*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((angle + corner)*PI/180) - dif2*sin(angle * PI / 180))*10)/10};
		rightB = 	{round((center.x + dia*cos((angle - corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((-angle + corner)*PI/180))*10)/10};
		leftT = 	{round((center.x - dia*cos((angle - corner)*PI/180) + dif1*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((-angle + corner)*PI/180) + dif1*sin(angle * PI / 180))*10)/10};
		leftB = 	{round((center.x - dia*cos((angle + corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((angle + corner)*PI/180))*10)/10};
	}
	void Trapeze::printOUT(ostream& out){
		out << "center " << "(" << center.x << ";" << center.y << ")" << endl;
    	out << "right top" << "(" << rightT.x << ";" << rightT.y << ")" << endl;
    	out << "right bottom" << "(" << rightB.x << ";" << rightB.y << ")" << endl;
    	out << "left top" << "(" << leftT.x << ";" << leftT.y << ")" << endl;
    	out << "left bottom" << "(" << leftB.x << ";" << leftB.y << ")" << endl;
    	out << "color " << color << endl; 
	}