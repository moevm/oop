#include "stdafx.h"
#include"base.h"
int Shape::ID = -1;
void Shape:: printShape()
{  
	int i =0;
	cout<< "ID фигуры: id=" << Id << "\n";
	cout << "Цвет: " << Color<< "\n";
	cout << "Центр : X = " << Centre.getX() << " ,Y = " << Centre.getY() << endl;
	while(i<4){
	    cout <<"Координата  вершины : X"<<i+1<<" = "<< this->Vertex[i].getX() << " ,Y"<<i+1<<" = " <<this-> Vertex[i].getY() << endl;
	    i++;
	}
}

void Shape::Turn(double& R)
{   cout << "Угол поворота: А = " << R << endl;
    for(int i=0;i<4;i++){
		Vertex[i] = Turnus(R,Vertex[i], Centre);
	}
}
void Shape:: move(double& x,double& y)
{   for(int i=0;i<4;i++){
		Vertex[i] = Movus(x,y,Vertex[i], Centre);
	}
	this->Centre.setX (x);
	this->Centre.setY (y);

}
void Shape:: Mahtab(double& P)
{   for(int i=0;i<4;i++){
		Vertex[i] = Mahtabus(P,Vertex[i], Centre);
	}
}
void Shape:: SetColorFigure(string &color)
{
    this->Color = color;
}
string Shape:: GetColorFigure()
{
	return Color;
}
bool Shape:: Dopfunction(Shape& shape2)
{   double arr1[3];double arr2[3];
	for(int i=0;i<4;i++)
	{   int m=i+1;
	    if(i==3) {m=0;}//чтобы построить сторону из первой и последней вершины
		//запоминаем коэффициенты прямой 0=Аx+By+C для стороны первой фигуры
		arr1[0]=Vertex[i].getY()-Vertex[m].getY();
	    arr1[1]=Vertex[m].getX()-Vertex[i].getX();
	    arr1[2]=(Vertex[i].getX()*Vertex[m].getY())-(Vertex[m].getX()*Vertex[i].getY());
		for(int j=0;j<4;j++)
		{   int r=i+1;
	        if(i==3) {r=0;}//запоминаем коэффициенты прямой 0=Аx+By+C для стороны второй фигуры
			arr2[0]=shape2.Vertex[j].getY()-shape2.Vertex[r].getY();
	        arr2[1]=shape2.Vertex[r].getX()-shape2.Vertex[j].getX();
	        arr2[2]=(shape2.Vertex[i].getX()*shape2.Vertex[r].getY())-(shape2.Vertex[r].getX()*shape2.Vertex[j].getY());
			if((arr1[0]==arr2[0]&&arr1[1]==arr2[1]&&arr1[2]==arr2[2])||(-arr1[0]==arr2[0]&&-arr1[1]==arr2[1]&&-arr1[2]==arr2[2])){
			//если уравнения прямых совпадают
			    if(Vertex[i].getX()!=Vertex[m].getX())//если прямая не вертикальна
				{    //если первый отрезок больше второго
					if((Vertex[i].getX()>=shape2.Vertex[r].getX()&&Vertex[i].getX()>=shape2.Vertex[j].getX()&&
					Vertex[m].getX()<=shape2.Vertex[r].getX()&&Vertex[m].getX()<=shape2.Vertex[j].getX())||	
					(Vertex[m].getX()>=shape2.Vertex[r].getX()&&Vertex[m].getX()>=shape2.Vertex[j].getX()&&
					Vertex[i].getX()<=shape2.Vertex[r].getX()&&Vertex[i].getX()<=shape2.Vertex[j].getX())||
					//если отрезок второй фигуры больше чем первой
				    (shape2.Vertex[j].getX()>=Vertex[m].getX()&&shape2.Vertex[j].getX()>=Vertex[i].getX()&&
					shape2.Vertex[r].getX()<=Vertex[m].getX()&&shape2.Vertex[r].getX()<=Vertex[i].getX())||	
					(shape2.Vertex[r].getX()>=Vertex[m].getX()&&shape2.Vertex[r].getX()>=Vertex[i].getX()&&
					shape2.Vertex[j].getX()<=Vertex[m].getX()&&shape2.Vertex[j].getX()<=Vertex[i].getX()))
					{
					    return true;
					}
				
				}
				else //сравниваем по  координате У
				{    //если первый отрезок больше второго
					if((Vertex[i].getY()>=shape2.Vertex[r].getY()&&Vertex[i].getY()>=shape2.Vertex[j].getY()&&
					Vertex[m].getY()<=shape2.Vertex[r].getY()&&Vertex[m].getY()<=shape2.Vertex[j].getY())||	
					(Vertex[m].getY()>=shape2.Vertex[r].getY()&&Vertex[m].getY()>=shape2.Vertex[j].getY()&&
					Vertex[i].getY()<=shape2.Vertex[r].getY()&&Vertex[i].getY()<=shape2.Vertex[j].getY())||
					//если отрезок второй фигуры больше чем первой
				    (shape2.Vertex[j].getY()>Vertex[m].getY()&&shape2.Vertex[j].getY()>=Vertex[i].getY()&&
					shape2.Vertex[r].getY()<=Vertex[m].getY()&&shape2.Vertex[r].getY()<=Vertex[i].getY())||	
					(shape2.Vertex[r].getY()>=Vertex[m].getY()&&shape2.Vertex[r].getY()>=Vertex[i].getY()&&
					shape2.Vertex[j].getY()<=Vertex[m].getY()&&shape2.Vertex[j].getY()<=Vertex[i].getY()))
					{
					    return true;
					}

				
				}
			}
		
		}

	}
	return false;
}
	