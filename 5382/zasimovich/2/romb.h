#pragma once
#include <string>
#include "base.h"
#include <iostream>
#include <math.h>
using namespace std;

class Rombus:public Shape
{
	public:
		Rombus( ){
			 double angle=180;
		     this->Centre = Point(true);
			 this->Vertex[0] = Point(true);
			 this->Vertex[1] = Point(true);
			 this-> Vertex[2]=Turnus(angle,Vertex[0],Centre);
	         this-> Vertex[3]=Turnus(angle,Vertex[1],Centre);
		
		
		
		};
		Rombus(Point& centre,Point& vertex1,Point& vertex2)
		{   if(sqrt(pow(Distance(centre,vertex1),2)+pow(Distance(centre,vertex2),2))!=Distance(vertex1,vertex2))
			throw invalid_argument("Диагонали ромба должны образовывать прямой угол");
			double angle=180;
	        cout << "ромб\n";
	        this->Centre = centre;
	        this->Vertex[0] = vertex1;
	        this->Vertex[1] = vertex2;
	        this-> Vertex[2]=Turnus(angle,Vertex[0],Centre);
	        this-> Vertex[3]=Turnus(angle,Vertex[1],Centre);
	        Id = ID;
	        ID++;
         }

		~Rombus(){cout << "ромб\n";}
   
};